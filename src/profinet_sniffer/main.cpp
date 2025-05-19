#include <iostream>
#include <tins/tins.h>

int main(int argc, char const *argv[])
{
    Tins::NetworkInterface iface = Tins::NetworkInterface::default_interface();

    Tins::SnifferConfiguration config;
    config.set_promisc_mode(true);
    config.set_filter("ether proto 0x8892"); // Filter for Profinet packets
    config.set_snap_len(65535); // Set maximum packet size
    config.set_immediate_mode(true);

    Tins::Sniffer sniffer(iface.name(), config);

    std::cout << "Listening on interface: " << iface.name() << std::endl;

    sniffer.sniff_loop([](Tins::PDU &pdu){
        Tins::EthernetII &eth = pdu.rfind_pdu<Tins::EthernetII>();
        std::cout << "Ethernet src: " << eth.src_addr()
        << "-> Dst: " << eth.dst_addr() << std::endl;

        const Tins::RawPDU *raw = pdu.find_pdu<Tins::RawPDU>();
        if (raw) {
            const Tins::RawPDU::payload_type &payload = raw->payload();
            
            if(payload.at(5) == 0x76) {
                std::cout << "Profinet packet detected, sensor value: " << payload.at(42) <<  std::endl;
            }

            std::cout << "Payload size: " << payload.size() << std::endl;
        }
        return true; // Continue sniffing
    });

    return 0;
}
