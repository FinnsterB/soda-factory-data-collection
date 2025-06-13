#include <iostream>
#include <cstdint>
#include <vector>
#include <sstream>
#include <tins/tins.h>
#include <signal.h>

#include "decode_pn_connect.h"
#include "decode_pnio_msg.h"

int main(int argc, char const *argv[])
{
    //Print sensor data for MAC from argument
    std::string verboseMAC = "";
    if(argc > 1){
        verboseMAC = argv[1];
    }

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
    sniffer.sniff_loop([&sysConfig, &verboseMAC](Tins::PDU &pdu){
        std::stringstream ssAddr;
        Tins::EthernetII &eth = pdu.rfind_pdu<Tins::EthernetII>();
        bool configMsg = false;
        try
        {
            Tins::UDP &udp = pdu.rfind_pdu<Tins::UDP>();
            if (udp.dport() == 34964)
            {
                configMsg = true;
            }
            
        }
        catch(const std::exception& e)
        {
            //std::cerr << e.what() << '\n';
        }

        ssAddr << eth.dst_addr();
        bool printPayload = false;
        
        const Tins::RawPDU *raw = pdu.find_pdu<Tins::RawPDU>();
        if (raw) {
            Tins::RawPDU::payload_type payload = raw->payload();
            if(configMsg == true){
                //Handle PN Connect messages
                sysConfig.handleConnect(ssAddr.str(), payload);
            }
            else{
                //Handle IO messages
                if(eth.src_addr() == verboseMAC){
                    Profinet::PNIO_msg::decodeMessage(verboseMAC, sysConfig.PLC_MAC, payload, sysConfig);
                }
            }
        }
        return true; // Continue sniffing
    });

    return 0;
}
