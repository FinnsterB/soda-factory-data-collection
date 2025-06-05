#include "decode_pn_connect.h"

bool Profinet::SystemConfiguration::deviceExists(PNDevice& device)
{
    for (auto& existingDevice : devices)
    {
        if (device.mac == existingDevice.mac)
        {
            return true;
        }
    }
    return false;
}

void Profinet::SystemConfiguration::handleConnect(const std::string& device_mac, std::vector<uint8_t>& data)
{
    PNDevice device(device_mac, "placeholder");
    device.parseConnectMessage(data);

    if (!deviceExists(device))
    {
        devices.push_back(device);
    }
    
}

void Profinet::SystemConfiguration::handleShutdown(int s)
{
    std::cout << "Unique Profinet devices found: " << devices.size() << std::endl;
}

Profinet::PNDevice::PNDevice(std::string aMac, std::string aName): mac(aMac), name(aName)
{
}

uint8_t Profinet::PNDevice::read8(std::vector<uint8_t>& data, uint16_t& offset){
    return data.at(offset++);
}

uint16_t Profinet::PNDevice::read16(std::vector<uint8_t>& data, uint16_t& offset){
    uint16_t result = 0;
    result = data.at(offset++);
    result << 8;
    result += data.at(offset++);
    return result;
}

uint32_t Profinet::PNDevice::read32(std::vector<uint8_t>& data, uint16_t& offset){
    uint32_t result = 0;
    result = data.at(offset++);
    result << 8;
    result += data.at(offset++);
    result << 8;
    result += data.at(offset++);
    result << 8;
    result += data.at(offset++);
    return result;
}

void Profinet::PNDevice::parseConnectMessage(std::vector<uint8_t>& data){
    std::cout << "Payload size: "<< data.size() << std::endl;
    if(data.size() < 200){
        return;
    }
    uint16_t offset = 0;
    offset += 80;// skip DCE/RPC data(80 bytes)
    offset += 20;// skip until first block BlockType;
    
    bool endOfPacket = false;
    while(endOfPacket){
        endOfPacket = parseConnectBlock(data, offset);
    }
}

bool Profinet::PNDevice::parseConnectBlock(std::vector<uint8_t> &data, uint16_t &offset)
{
    uint16_t blockType = read16(data, offset);
    switch (blockType)
    {
        case BlockTypes::ARBlockReq_nr:
        {
            std::cout << "ARBlockReq\n";
            // This case is not relevant, the block will be skipped.
            uint16_t skipARBlock = read16(data, offset);
            std::cout << "ARBlockLenght: " << skipARBlock << "\n";
            offset += skipARBlock;
            break;
        }
        case BlockTypes::IOCRBlockReq_nr:
        {
            std::cout << "IOCRBlockReq\n";
            // This case is relevant, API data and offsets get parsed from the block.
            offset += 2; // skip to IOCRType
            uint16_t IOCRType = read16(data, offset);
            offset += 42;// skip to NumberOfAPIS
            uint16_t loopAmount = read16(data, offset);
            std::cout << "IOCRBlockReq number of api's: " << loopAmount << " at offset " << offset << "\n";
            for(uint16_t i = 0; i < loopAmount; i++)
            {
                offset += 4;
                uint16_t numOfIODataObjs = read16(data, offset);
                std::cout << "Api " << i << " has: " << numOfIODataObjs << " IODataObjects" << "\n";

                API_IO_Data api;
                for (uint16_t j = 0; j < numOfIODataObjs; j++)
                {
                    IODataObject obj;
                    obj.slot = read16(data, offset);

                    obj.subslot = read16(data, offset);

                    obj.offset = read16(data, offset);
                    api.io_data_objects.push_back(obj);
                }

                uint16_t numOfIOCS = read16(data, offset);
                
                for (uint16_t j = 0; j < numOfIOCS; j++)
                {
                    IOCS iocs;
                    iocs.slot = read16(data, offset);

                    iocs.subslot = read16(data, offset);

                    iocs.offset = read16(data, offset);
                    api.iocs_s.push_back(iocs);
                }
                switch (IOCRType)
                {
                case IOCRTypes::InputCR:
                    input.apis.push_back(api);
                    break;
                case IOCRTypes::OutputCR:
                    output.apis.push_back(api);
                    break;
                }
                input.apis.push_back(api);
            }
            break;
        }
        case BlockTypes::AlarmCRBlockReq_nr:
        {
            std::cout << "AlarmCRBlockReq\n";
            // This case is not relevant, the block will be skipped.
            uint16_t skipAlarmBlock = read16(data, offset);
            std::cout << "AlarmBlockLenght: " << skipAlarmBlock << "\n";
            offset += skipAlarmBlock;
            break;
        }
        case BlockTypes::ExpectedSubmoduleBlockReq_nr:
        {
            std::cout << "ExpectedSubmoduleBlockReq\n";
            ExpectedSubmoduleBlockReq expectedSubmoduleBlockReq;
            //This case is relevant, GSDML module and submodule ID's and data lengths will be parsed from the block.
            offset += 4;
            uint16_t numOfApis = read16(data, offset);
            std::cout << "ExpectedSubmodule numOfApis: " << numOfApis << "\n";
            for (uint16_t i = 0; i < numOfApis; i++)
            {
                API_Module_Info api;
                // skip to nr of submodules
                offset += 14;
                uint16_t nrOfSubmodules = read16(data, offset);
                for (uint16_t j = 0; j < nrOfSubmodules; j++)
                {
                    Submodule submodule;
                    submodule.subslot = read16(data, offset);
                    submodule.submoduleIdentNr = read32(data, offset);
                    submodule.dataDescription.dataDescription = read16(data, offset);
                    submodule.dataDescription.SubmoduleDataLength = read16(data, offset);
                    submodule.dataDescription.IOCSLength = read8(data, offset);
                    submodule.dataDescription.IOPSLength = read8(data, offset);
                }
                
            }
            expectedSubmodules.push_back(expectedSubmoduleBlockReq);
            break;
        }
        default:
            std::cerr << "Malformed block, aborting parser.\n" << std::endl;
            return false;
            break; 
    }
    //Return if last block
    //std::cout << "Current offset: " << offset << " Payload size: " << data.size() << "\n";
    return offset == data.size();
}
