#include "decode_pn_connect.h"

#include <cstring>

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
    std::cout << "Parsing Connect Message from MAC: " << device_mac << std::endl;
    device.parseConnectMessage(data);

    if (!deviceExists(device))
    {
        devices.push_back(device);
        std::cout << "New Device Found with MAC: " << device_mac << "\nInput interfaces:\n";
        std::vector<std::pair<uint16_t, uint16_t>> offsetAndLengthInput;
        std::vector<std::pair<uint16_t, uint16_t>> offsetAndLengthOutput;
        for (uint16_t i = 0; i < device.input.apis.size(); i++)
        {
            for (uint16_t j = 0; j < device.input.apis.at(i).io_data_objects.size(); j++)
            {
                std::pair<uint16_t, uint16_t> interface;
                interface.first = device.input.apis.at(i).io_data_objects.at(j).offset;
                interface.second = device.expectedSubmodules.at(i).apis.at(0).submodules.at(j).dataDescriptions.at(0).SubmoduleDataLength;
                offsetAndLengthInput.push_back(interface);
            }
            
        }
        for (uint16_t i = 0; i < device.output.apis.size(); i++)
        {
            for (uint16_t j = 0; j < device.output.apis.at(i).io_data_objects.size(); j++)
            {
                std::pair<uint16_t, uint16_t> interface;
                interface.first = device.output.apis.at(i).io_data_objects.at(j).offset;
                interface.second = device.expectedSubmodules.at(i).apis.at(0).submodules.at(j).dataDescriptions.at(0).SubmoduleDataLength;
                offsetAndLengthOutput.push_back(interface);
            }
            
        }
        uint16_t counter = 0;
        for (auto& ol : offsetAndLengthInput)
        {
            std::cout << "Input interface | " << counter++ << " Data Offset: " << ol.first << " Length: " << ol.second << "\n";
        }
        counter = 0;
        for (auto& ol : offsetAndLengthOutput)
        {
            std::cout << "Output interface | " << counter++ << " Data Offset: " << ol.first << " Length: " << ol.second << "\n";
        }
        
    }
    
}

Profinet::PNDevice::PNDevice(std::string aMac, std::string aName): mac(aMac), name(aName)
{
}

uint8_t Profinet::PNDevice::read8(const std::vector<uint8_t>& data, uint16_t& offset) {
    return data.at(offset++);
}


uint16_t Profinet::PNDevice::read16(const std::vector<uint8_t>& data, uint16_t& offset) {
    uint16_t result = (static_cast<uint16_t>(data.at(offset)) << 8) |
                      static_cast<uint16_t>(data.at(offset + 1));
    offset += 2;
    return result;
}


uint32_t Profinet::PNDevice::read32(const std::vector<uint8_t>& data, uint16_t& offset) {
    uint32_t result = (static_cast<uint32_t>(data.at(offset)) << 24) |
                      (static_cast<uint32_t>(data.at(offset + 1)) << 16) |
                      (static_cast<uint32_t>(data.at(offset + 2)) << 8) |
                      static_cast<uint32_t>(data.at(offset + 3));
    offset += 4;
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
    while(!endOfPacket){
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
            offset += 4; // skip to IOCRType
            uint16_t IOCRType = read16(data, offset);
            offset += 36;// skip to NumberOfAPIS
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
                offset += 4; //Skip API nr
                api.slot = read16(data, offset);
                offset += 6; //Skip ModuleIdentNr and properties
                uint16_t nrOfSubmodules = read16(data, offset);
                for (uint16_t j = 0; j < nrOfSubmodules; j++)
                {
                    Submodule submodule;
                    submodule.subslot = read16(data, offset);
                    submodule.submoduleIdentNr = read32(data, offset);
                    offset += 2; // Skip submodule properties.
                    //Apparently there can be multiple dataDescriptions: 
                    for (uint16_t k = 0; k < requiredDataDescriptionAmount(api.slot, submodule.subslot); k++)
                    {
                        DataDescription dataDesc;
                        dataDesc.dataDescription = read16(data, offset);
                        dataDesc.SubmoduleDataLength = read16(data, offset);
                        dataDesc.IOCSLength = read8(data, offset);
                        dataDesc.IOPSLength = read8(data, offset);
                        submodule.dataDescriptions.push_back(dataDesc);
                    }
                    
                    api.submodules.push_back(submodule);
                }
                expectedSubmoduleBlockReq.apis.push_back(api);
            }
            expectedSubmodules.push_back(expectedSubmoduleBlockReq);
            break;
        }
        default:
            std::cerr << "Malformed block or end of packet, aborting parser.\n" << std::endl;
            offset = data.size();
            return false;
            break;
    }
    //Return if last block
    //std::cout << "Current offset: " << offset << " Payload size: " << data.size() << "\n";
    return offset == data.size();
}

uint8_t Profinet::PNDevice::requiredDataDescriptionAmount(const uint16_t slotNr, const uint16_t subslotNr)
{
    bool input_exists = false;
    bool output_exists = false;
    for (auto& inputSubslot : input.apis)
    {
          for(auto& io_d_obj : inputSubslot.io_data_objects) {
            if (io_d_obj.subslot == subslotNr && io_d_obj.slot == slotNr)
            {
                input_exists = true;
            }
            
          }
    }
    for (auto& outputSubslot : output.apis)
    {
          for(auto& io_d_obj : outputSubslot.io_data_objects) {
            if (io_d_obj.subslot == subslotNr && io_d_obj.slot == slotNr)
            {
                output_exists = true;
            }
            
          }
    }
    return (uint8_t)input_exists + output_exists;
}
