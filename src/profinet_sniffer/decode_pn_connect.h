#ifndef DECODE_PN_CONNECT_H
#define DECODE_PN_CONNECT_H

#include <iostream>
#include <vector>

namespace Profinet{

    struct IODataObject{
        uint16_t slot;
        uint16_t subslot;
        uint16_t offset;
    };

    struct IOCS{
        uint16_t slot;
        uint16_t subslot;
        uint16_t offset;
    };

    struct Submodule{
        uint16_t subslot;
        uint32_t submoduleIdentNr;
    };

    struct API_IO_Data{
        std::vector<IODataObject> io_data_objects;
        std::vector<IOCS> iocs_s;
    };

    struct API_Module_Info{
        std::vector<Submodule> submodules;
    };

    struct IOCRBlockReq{
        uint16_t iocr_type;
        std::vector<API_IO_Data> apis;
    };

    struct ExpectedSubmoduleBlockReq{
        std::vector<API_Module_Info> apis;
    };


    class PNDevice
    {
    public:
        PNDevice(std::string aMac, std::string aName);
        bool isConfigured;
        std::string mac;
        std::string name;
        IOCRBlockReq input;
        IOCRBlockReq output;
        std::vector<ExpectedSubmoduleBlockReq> expectedSubmodules;


        /**
         * @brief: Reads a uint8_t from data vector.
         */
        uint8_t read8(std::vector<uint8_t>& data, uint16_t& offset);

        /**
         * @brief: Reads a uint16_t from data vector.
         */
        uint16_t read16(std::vector<uint8_t>& data, uint16_t& offset);

        /**
         * @brief: Reads a uint32_t from data vector.
         */
        uint32_t read32(std::vector<uint8_t>& data, uint16_t& offset);

        void parseConnectMessage(std::vector<uint8_t>& data);
    };


    /**
     * Profinet system configuration: Holds all Profinet devices except for the 
     * Controller(PLC). For the purposes of this network the PLC is not included
     * here.
     */
    class SystemConfiguration
    {
    public:
        SystemConfiguration(){};
        bool deviceExists(PNDevice& device);
        void handleConnect(const std::string& device_mac, std::vector<uint8_t>& data);
        void handleShutdown(int s);
        std::vector<PNDevice> devices;
    };

};

#endif