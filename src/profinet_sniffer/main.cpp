#include <iostream>
#include <vector>
#include <sstream>
#include <tins/tins.h>
#include <signal.h>

#include "decode_pn_connect.h"

struct IO_Link_AL1303{
    std::string mac;
    std::vector<uint8_t> ip;
    std::vector<uint8_t> offsets;
    std::vector<uint8_t> lengths;
};

IO_Link_AL1303 xg1;
IO_Link_AL1303 xg2;
IO_Link_AL1303 xg3;
IO_Link_AL1303 xg4;
IO_Link_AL1303 xg5;

void setupMasters(){
    xg1.mac = "00:02:01:0a:28:02";
    xg2.mac = "00:02:01:05:70:76";
    xg3.mac = "00:02:01:05:cd:9e";
    xg4.mac = "00:02:01:05:72:8e";
    xg5.mac = "00:02:01:0a:27:d3";

    xg1.offsets = {5,11,17,19,21,23,25,35};
    xg1.lengths = {5,5,1,1,1,1,9,0};

    xg2.offsets = {5,6,10,14,18,22,28,30};
    xg2.lengths = {0,3,3,3,3,5,1,1};

    xg3.offsets = {};
    xg3.lengths = {};

    xg4.offsets = {};
    xg4.lengths = {};

    xg5.offsets = {};
    xg5.lengths = {};

}

int main(int argc, char const *argv[])
{
    //setupMasters();
    Tins::NetworkInterface iface("lo");
    Tins::SnifferConfiguration config;
    config.set_promisc_mode(true);
    config.set_filter("ether proto 0x8892 or (udp dst port 34964)"); // Filter for Profinet packets and connect messages
    config.set_snap_len(65535); // Set maximum packet size
    config.set_immediate_mode(true);
    
    

    Tins::Sniffer sniffer(iface.name(), config);

    std::cout << "Listening on interface: " << iface.name() << std::endl;

    Profinet::SystemConfiguration sysConfig;

    sniffer.sniff_loop([&sysConfig](Tins::PDU &pdu){
        std::stringstream ssAddr;
        Tins::EthernetII &eth = pdu.rfind_pdu<Tins::EthernetII>();
        bool configMsg = false;
        try
        {
            Tins::UDP &udp = pdu.rfind_pdu<Tins::UDP>();
            configMsg = true;
        }
        catch(const std::exception& e)
        {
            //std::cerr << e.what() << '\n';
        }
        //std::cout << "Ethernet src: " << eth.src_addr()
        //<< "-> Dst: " << eth.dst_addr() << std::endl;
        ssAddr << eth.dst_addr();
        bool printPayload = false;
        
        const Tins::RawPDU *raw = pdu.find_pdu<Tins::RawPDU>();
        if (raw) {
            Tins::RawPDU::payload_type payload = raw->payload();
            if(configMsg == true){
                sysConfig.handleConnect(ssAddr.str(), payload);
                sysConfig.handleShutdown(1);
            }
            else{
                //std::cout << "IO_data_message from: " << eth.src_addr() << "\n";
            }
        }
        return true; // Continue sniffing
    });

    return 0;
}
