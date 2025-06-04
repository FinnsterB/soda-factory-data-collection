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
    
    parseConnectBlock(data, offset);

}

void Profinet::PNDevice::parseConnectBlock(std::vector<uint8_t> &data, uint16_t &offset)
{
    uint16_t blockType = read16(data, offset);
    switch (blockType)
    {
    case BlockTypes::ARBlockReq_nr:
        // This case is not relevant, the block will be skipped.
        uint16_t skip = read16(data, offset);
        offset += skip;
        break;
    case BlockTypes::IOCRBlockReq_nr:
        // This case is relevant, API data and offsets get parsed from the block.
        offset += 44;// skip to NumberOfAPIS
        uint16_t loopAmount = read16(data, offset);
        std::cout << "IOCRBlockReq number of api's: " << loopAmount << " at offset " << offset << std::endl;
        for(uint16_t i = 0; i < loopAmount; i++)
        {
            offset += 4;
            uint16_t numOfIODataObjs = read16(data, offset);
            std::cout << "Api " << i << " has: " << numOfIODataObjs << " IODataObjects" << std::endl;

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
            std::cout << "Parsed " << api.io_data_objects.size() << " IODataObjects." << std::endl;
            std::cout << "Parsed " << api.iocs_s.size() << " IOCS's." << std::endl;
            input.apis.push_back(api);
        }
        break;
    case BlockTypes::AlarmCRBlockReq_nr:
        // This case is not relevant, the block will be skipped.
        uint16_t skip = read16(data, offset);
        offset += skip;
        break;
    case BlockTypes::ExpectedSubmoduleBlockReq_nr:
        //This case is relevant, GSDML module and submodule ID's will be parsed from the block.
        break;
    default:
        break;
    }
}
