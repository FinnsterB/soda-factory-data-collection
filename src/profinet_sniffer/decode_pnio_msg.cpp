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

void Profinet::PNIO_msg::decodeMessage(std::string src_mac, std::string dst_mac, std::vector<uint8_t> data, Profinet::SystemConfiguration& sysConfig)
{
    Profinet::DeviceInterface offsetsAndLengths = sysConfig.getDeviceDataOffsets(src_mac, dst_mac);
    std::vector<uint64_t> values;
    for(std::pair<uint16_t, uint16_t>& ol : offsetsAndLengths){
        switch (ol.second)
        {
        case 0:
            values.push_back(PNUtils::read8(data, ol.first));
            break;
        case 1:

            break;
        case 2:

            break;
        case 3:

            break;
        case 4:

            break;
        default:
            
            break;
        }
    }
}
