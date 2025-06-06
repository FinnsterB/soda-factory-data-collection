#ifndef DECODE_PN_CONNECT_H
#define DECODE_PN_CONNECT_H

#include <iostream>
#include <vector>

namespace Profinet{
    enum BlockTypes{
        ARBlockReq_nr = 0x0101,
        IOCRBlockReq_nr = 0x0102,
        AlarmCRBlockReq_nr = 0x0103,
        ExpectedSubmoduleBlockReq_nr = 0x0104
    };

    enum IOCRTypes{
        InputCR = 0x0001,
        OutputCR = 0x0002
    };

    struct IODataObject{
        uint16_t slot;
        uint16_t subslot;
        uint16_t offset;
        //Not sure if it is a good idea to use this or put it in it's own struct Submodule:
        uint16_t length;
    };

    /**
     * @brief According to Siemens documentation from: https://support.industry.siemens.com/dl/files/145/109781145/att_1028016/v1/pn_driver_IO-Base_user_programming_interface_en-US.pdf
     * the IOCS is the Consumer status. When the PLC sends data TO a device, the PLC is a provider and the device is the consumer. The Consumer Status represents how the consumer
     * handled the last message: it can be either good or bad. This works the same way in the opposite direction: from Device to PLC. I will not use this status information for now.
     */
    struct IOCS{
        uint16_t slot;
        uint16_t subslot;
        uint16_t offset;
    };

    struct DataDescription{
        uint16_t dataDescription;
        uint16_t SubmoduleDataLength;
        uint8_t IOCSLength;
        uint8_t IOPSLength;
    };

    struct Submodule{
        uint16_t subslot;
        uint32_t submoduleIdentNr;
        DataDescription dataDescription;
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

    /**
     * @brief Contains API Module info, which holds the data lengths for IO-data. The data lengths together with the data offsets can be used to decode PN-IO messages. 
     */
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
         * @brief: Reads a uint8_t from data vector. Offset gets incremented each byte.
         * Would use std::memcpy for this but te ethernet payload is big-endian.
         */
        uint8_t read8(const std::vector<uint8_t>& data, uint16_t& offset);

        /**
         * @brief: Reads a uint16_t from data vector. Offset gets incremented each byte. 
         * Would use std::memcpy for this but te ethernet payload is big-endian.
         */
        uint16_t read16(const std::vector<uint8_t>& data, uint16_t& offset);

        /**
         * @brief: Reads a uint32_t from data vector. Offset gets incremented each byte. 
         * Would use std::memcpy for this but the ethernet payload is big-endian.
         */
        uint32_t read32(const std::vector<uint8_t>& data, uint16_t& offset);

        /**
         * @brief: Parses a connect message that configures a Profinet slave device.
         */
        void parseConnectMessage(std::vector<uint8_t>& data);

        /**
         * @brief: Parses a PNIO Connect Block
         * 
         * @returns: bool that signifies if the end of the message has been reached.
         */
        bool parseConnectBlock(std::vector<uint8_t>& data, uint16_t& offset);
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