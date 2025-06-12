#ifndef DECODE_PNIO_MSG_H
#define DECODE_PNIO_MSG_G

#include "decode_pn_connect.h"

#include <iostream>
#include <vector>

namespace Profinet{
    class PNIO_msg{
        /**
         * @brief This function will decode the message using the src MAC address and dst MAC address
         * to determine what decoder needs to be used. 
         */
        static void decodeMessage(std::string src_mac, std::string dst_mac, std::vector<uint8_t> data);
        /**
         * 
         */
    };
};


#endif