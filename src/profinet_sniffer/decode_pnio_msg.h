#ifndef DECODE_PNIO_MSG_H
#define DECODE_PNIO_MSG_G

#include "decode_pn_connect.h"

#include <iostream>
#include <cstdint>
#include <vector>

namespace Profinet{
    class PNUtils{
        public:
                /**
         * @brief: Reads a uint8_t from data vector. Offset gets incremented each byte.
         * Would use std::memcpy for this but te ethernet payload is big-endian.
         */
        static uint8_t read8(const std::vector<uint8_t>& data, uint16_t& offset);

        /**
         * @brief: Reads a uint16_t from data vector. Offset gets incremented each byte. 
         * Would use std::memcpy for this but te ethernet payload is big-endian.
         */
        static uint16_t read16(const std::vector<uint8_t>& data, uint16_t& offset);

        /**
         * @brief: Reads a uint32_t from data vector. Offset gets incremented each byte. 
         * Would use std::memcpy for this but the ethernet payload is big-endian.
         */
        static uint32_t read32(const std::vector<uint8_t>& data, uint16_t& offset);
        /**
         * @brief: Reads a uint64_t from data vector. Offset gets incremented each byte. 
         * Would use std::memcpy for this but the ethernet payload is big-endian.
         */
        static uint64_t read64(const std::vector<uint8_t>& data, uint16_t& offset);
    };

    class PNIO_msg{
        public:
        /**
         * @brief This function will decode the message using the src MAC address and dst MAC address
         * to determine what decoder needs to be used. 
         */
        static void decodeMessage(std::string src_mac, std::string dst_mac, std::vector<uint8_t> data, SystemConfiguration& sysConfig);
        /**
         * 
         */
    };
};


#endif