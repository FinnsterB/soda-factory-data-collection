#include "decode_pn_connect.h"
#include "decode_pnio_msg.h"
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
    
    //TODO: This checks if the device exists already in two different ways, fix later.
    if(!getDevice(device_mac).has_value()){
        std::cout << "Parsing Connect Message for MAC: " << device_mac << "\n\n";
        device.parseConnectMessage(data);
    }


    updateDevice(device);
    DeviceInterface offsetAndLengthInput = getDeviceDataOffsets(device_mac, PLC_MAC);
    DeviceInterface offsetAndLengthOutput = getDeviceDataOffsets(PLC_MAC, device_mac);
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
    std::cout << std::endl;
    
}

void Profinet::SystemConfiguration::handleIdentify(const std::string &device_mac, std::vector<uint8_t> &data)
{
    //From this block only the Name of Station, VendorID and DeviceID are required:

    
    uint16_t offset = 10; // Skip FrameID and ServiceID/Type
    uint16_t DCPDataLength = PNUtils::read16(data, offset); //Total length of DCP blocks combined.
    DeviceIdentification deviceIdentification;
    deviceIdentification.MAC = device_mac;
    bool endOfData = false;
    while(!endOfData){
        uint16_t option = PNUtils::read8(data, offset); //DCP blocks always start with an option byte
        uint16_t subOption = PNUtils::read8(data, offset); //followed by a suboption byte.

        //Followed by the length of the block. 
        switch (option)
        {
        case IdentifyOptions::DeviceProperties_nr:
            switch (subOption)
            {
            case IdentifyDevicePropertiesSubOptions::TypeOfStation_nr:
            {
                uint16_t blockLength = PNUtils::read16(data, offset);
                offset += 2; //Skip reserved bytes
                for (uint16_t i = 2; i < blockLength; i++) //Loop starts at 2 because it needs to skip the reserved BlockInfo bytes.
                {
                    deviceIdentification.typeOfStation.push_back(PNUtils::read8(data, offset));
                }
                offset++; //Skip padding byte after string value.
                endOfData = offset + 1 > DCPDataLength; //Check if max length is reached.
                break;
            }
            case IdentifyDevicePropertiesSubOptions::NameOfStation_nr:
            {
                uint16_t blockLength = PNUtils::read16(data, offset);
                offset += 2; //Skip reserved bytes
                for (uint16_t i = 2; i < blockLength; i++) //Loop starts at 1 because it needs to skip the reserved BlockInfo bytes.
                {
                    deviceIdentification.nameOfStation.push_back(PNUtils::read8(data, offset));
                }
                offset++; //Skip padding byte after string value.
                endOfData = offset + 1 > DCPDataLength; //Check if max length is reached.
                break;
            }
            case IdentifyDevicePropertiesSubOptions::DeviceID_nr:
            {
                uint16_t blockLength = PNUtils::read16(data, offset);
                offset += 2; //Skip reserved bytes
                deviceIdentification.vendorID = PNUtils::read16(data, offset);
                deviceIdentification.deviceID = PNUtils::read16(data, offset);
                endOfData = offset + 1 > DCPDataLength; //Check if max length is reached.
                break;
            }
            default:
                uint16_t blockLength = PNUtils::read16(data, offset);
                offset += blockLength;
                endOfData = offset + 1 > DCPDataLength; //Check if max length is reached.
                break;
            }
            break;
        default: //Only need the Device Properties, IP is usually not set yet and we can get it from the eth/ip data.
            uint16_t blockLength = PNUtils::read16(data, offset);
            offset += blockLength;
            endOfData = offset + 1 > DCPDataLength; //Check if max length is reached.
            break;
        }
    }

    updateDeviceIdentification(deviceIdentification);
}

Profinet::DeviceInterface Profinet::SystemConfiguration::getDeviceDataOffsets(const std::string &src_mac, const std::string &dst_mac)
{

    Profinet::DeviceInterface offsetAndLength;
    //Get the device that is not the master(PLC), to determine data direction:
    std::string deviceMac = PLC_MAC == src_mac ? dst_mac : src_mac;

    //If the data is going from Device to PLC then we consider it to come from an input.
    bool isInput = PLC_MAC == dst_mac;
    
    std::optional<PNDevice> device = getDevice(deviceMac);
    if (device.has_value())
    {
        if(isInput)
        {
            //If the master is dst then get the input API;
            for (uint16_t i = 0; i < device.value().input.apis.size(); i++)
            {
                for (auto& io_obj : device.value().input.apis.at(i).io_data_objects)
                {
                    std::pair<uint16_t, uint16_t> interface;
                    interface.first = io_obj.offset;
                    //This following line only handles the first dataDescription
                    interface.second = device.value().getDataDescriptionBySubslot(io_obj.slot, io_obj.subslot).SubmoduleDataLength;
                    offsetAndLength.push_back(interface);
                }
            }
        }
        else
        {
            //If the master is src then get the output API;
            for (uint16_t i = 0; i < device.value().output.apis.size(); i++)
            {
                for (auto& io_obj : device.value().output.apis.at(i).io_data_objects)
                {
                    std::pair<uint16_t, uint16_t> interface;
                    interface.first = io_obj.offset;
                    //This following line only handles the first dataDescription
                    interface.second = device.value().getDataDescriptionBySubslot(io_obj.slot, io_obj.subslot).SubmoduleDataLength;
                    offsetAndLength.push_back(interface);
                }
            }
        }
    }
    

    return offsetAndLength;
    
}

std::optional<Profinet::PNDevice> Profinet::SystemConfiguration::getDevice(std::string deviceMAC)
{
    for (PNDevice& d : devices)
    {
        if(d.mac == deviceMAC){
            return d;
        }
    }
    return std::nullopt;
}

void Profinet::SystemConfiguration::updateDevice(PNDevice device)
{
    //Loop though devices to find the same MAC-address:
    for (PNDevice& existingDevice : devices)
    {
        if(existingDevice.mac == device.mac){
            existingDevice = device;
            std::cout << "Updated configuration of " << device.mac << '\n';
            return;
        }
    }
    devices.push_back(device);
}

void Profinet::SystemConfiguration::updateDeviceIdentification(DeviceIdentification devIdent)
{
    //Loop though devices to find the same MAC-address:
    for(DeviceIdentification& existingDevIdent : deviceIdentifications){
        if(existingDevIdent.MAC == devIdent.MAC){
            existingDevIdent = devIdent;
            std::cout << "Updated identity of " << existingDevIdent.MAC << '\n';
            return;
        }
    }
    deviceIdentifications.push_back(devIdent);
}

Profinet::PNDevice::PNDevice(std::string aMac, std::string aName): mac(aMac), name(aName)
{
}

Profinet::DataDescription Profinet::PNDevice::getDataDescriptionBySubslot(uint16_t slot, uint16_t subslot)
{
    for (auto& blockReq : expectedSubmodules)
    {
        for(auto& api : blockReq.apis){
            if(api.slot == slot){
                for (auto& subModule : api.submodules)
                {
                    if (subModule.subslot == subslot && !subModule.dataDescriptions.empty())
                    {
                        return subModule.dataDescriptions.at(0);
                    }
                    
                }
                
            }
            
        }
    }
    
    return DataDescription();
}

void Profinet::PNDevice::parseConnectMessage(std::vector<uint8_t> &data)
{
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
    uint16_t blockType = PNUtils::read16(data, offset);
    switch (blockType)
    {
        case BlockTypes::ARBlockReq_nr:
        {
            // This case is not relevant, the block will be skipped.
            uint16_t skipARBlock = PNUtils::read16(data, offset);
            offset += skipARBlock;
            break;
        }
        case BlockTypes::IOCRBlockReq_nr:
        {
            // This case is relevant, API data and offsets get parsed from the block.
            offset += 4; // skip to IOCRType
            uint16_t IOCRType = PNUtils::read16(data, offset);
            offset += 36;// skip to NumberOfAPIS
            uint16_t loopAmount = PNUtils::read16(data, offset);
            for(uint16_t i = 0; i < loopAmount; i++)
            {
                offset += 4;
                uint16_t numOfIODataObjs = PNUtils::read16(data, offset);

                API_IO_Data api;
                for (uint16_t j = 0; j < numOfIODataObjs; j++)
                {
                    IODataObject obj;
                    obj.slot = PNUtils::read16(data, offset);

                    obj.subslot = PNUtils::read16(data, offset);

                    obj.offset = PNUtils::read16(data, offset);
                    api.io_data_objects.push_back(obj);
                }

                uint16_t numOfIOCS = PNUtils::read16(data, offset);
                
                for (uint16_t j = 0; j < numOfIOCS; j++)
                {
                    IOCS iocs;
                    iocs.slot = PNUtils::read16(data, offset);

                    iocs.subslot = PNUtils::read16(data, offset);

                    iocs.offset = PNUtils::read16(data, offset);
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
            // This case is not relevant, the block will be skipped.
            uint16_t skipAlarmBlock = PNUtils::read16(data, offset);
            offset += skipAlarmBlock;
            break;
        }
        case BlockTypes::ExpectedSubmoduleBlockReq_nr:
        {
            ExpectedSubmoduleBlockReq expectedSubmoduleBlockReq;
            //This case is relevant, GSDML module and submodule ID's and data lengths will be parsed from the block.
            offset += 4;
            uint16_t numOfApis = PNUtils::read16(data, offset);
            for (uint16_t i = 0; i < numOfApis; i++)
            {
                API_Module_Info api;
                // skip to nr of submodules
                offset += 4; //Skip API nr
                api.slot = PNUtils::read16(data, offset);
                offset += 6; //Skip ModuleIdentNr and properties
                uint16_t nrOfSubmodules = PNUtils::read16(data, offset);
                for (uint16_t j = 0; j < nrOfSubmodules; j++)
                {
                    Submodule submodule;
                    submodule.subslot = PNUtils::read16(data, offset);
                    submodule.submoduleIdentNr = PNUtils::read32(data, offset);
                    offset += 2; // Skip submodule properties.
                    //Apparently there can be multiple dataDescriptions: 
                    for (uint16_t k = 0; k < requiredDataDescriptionAmount(api.slot, submodule.subslot); k++)
                    {
                        DataDescription dataDesc;
                        dataDesc.dataDescription = PNUtils::read16(data, offset);
                        dataDesc.SubmoduleDataLength = PNUtils::read16(data, offset);
                        dataDesc.IOCSLength = PNUtils::read8(data, offset);
                        dataDesc.IOPSLength = PNUtils::read8(data, offset);
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
