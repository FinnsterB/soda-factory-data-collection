#include "decode_pnio_msg.h"

/*static*/uint8_t Profinet::PNUtils::read8(const std::vector<uint8_t>& data, uint16_t& offset) {
    return data.at(offset++);
}


/*static*/uint16_t Profinet::PNUtils::read16(const std::vector<uint8_t>& data, uint16_t& offset) {
    uint16_t result = (static_cast<uint16_t>(data.at(offset)) << 8) |
                      static_cast<uint16_t>(data.at(offset + 1));
    offset += 2;
    return result;
}


/*static*/uint32_t Profinet::PNUtils::read32(const std::vector<uint8_t>& data, uint16_t& offset) {
    uint32_t result = (static_cast<uint32_t>(data.at(offset)) << 24) |
                      (static_cast<uint32_t>(data.at(offset + 1)) << 16) |
                      (static_cast<uint32_t>(data.at(offset + 2)) << 8) |
                      static_cast<uint32_t>(data.at(offset + 3));
    offset += 4;
    return result;
}

/*static*/ uint64_t Profinet::PNUtils::read64(const std::vector<uint8_t>& data, uint16_t& offset) {
    uint64_t result = (static_cast<uint64_t>(data.at(offset))     << 56) |
                      (static_cast<uint64_t>(data.at(offset + 1)) << 48) |
                      (static_cast<uint64_t>(data.at(offset + 2)) << 40) |
                      (static_cast<uint64_t>(data.at(offset + 3)) << 32) |
                      (static_cast<uint64_t>(data.at(offset + 4)) << 24) |
                      (static_cast<uint64_t>(data.at(offset + 5)) << 16) |
                      (static_cast<uint64_t>(data.at(offset + 6)) << 8)  |
                      static_cast<uint64_t>(data.at(offset + 7));
    offset += 8;
    return result;
}


void Profinet::PNIO_msg::decodeMessage(std::string src_mac, std::string dst_mac, std::vector<uint8_t> data, Profinet::SystemConfiguration& sysConfig)
{
    Profinet::DeviceInterface offsetsAndLengths = sysConfig.getDeviceDataOffsets(src_mac, dst_mac);
    std::vector<uint64_t> values;
    for(std::pair<uint16_t, uint16_t> ol : offsetsAndLengths){ // Not using a reference on purpose, read() function increments the offset.
        switch (ol.second)
        {
        case 0:
            values.push_back(PNUtils::read8(data, ol.first));
            break;
        case 1:
            values.push_back(PNUtils::read8(data, ol.first));
            break;
        case 2:
            values.push_back(PNUtils::read16(data, ol.first));
            break;
        case 3:
            values.push_back(PNUtils::read16(data, ol.first));
            break;
        case 4:
            values.push_back(PNUtils::read32(data, ol.first));
            break;
        case 5:
            values.push_back(PNUtils::read32(data, ol.first));
            break;
        case 8:
            values.push_back(PNUtils::read64(data, ol.first));
            break;
        case 9:
            values.push_back(PNUtils::read64(data, ol.first));
            break;
        default:
            values.push_back(404);
            break;
        }
    }
    //For demo purposes we will just print the values, in the future this gets sent to the dataHAndler.
    if(values.empty()){
        std::cout << src_mac << " has no values, probably not decoded yet." << std::endl;
    }else{
        std::cout << src_mac << " | values: ";
    }
    for(uint64_t value : values){
        std::cout << '\t' << value;
    }

    std::cout << '\n';
}
