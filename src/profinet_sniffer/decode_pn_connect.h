#ifndef DECODE_PN_CONNECT_H
#define DECODE_PN_CONNECT_H

#include <iostream>
#include <cstdint>
#include <vector>
#include <utility>
#include <optional>

namespace Profinet{
    /**
     * @brief: The deviceInterface is a vector with the data length and offset in a pair<length, offset>
     */
    typedef std::vector<std::pair<uint16_t, uint16_t>> DeviceInterface;


    enum BlockTypes{
        ARBlockReq_nr = 0x0101,
        IOCRBlockReq_nr = 0x0102,
        AlarmCRBlockReq_nr = 0x0103,
        ExpectedSubmoduleBlockReq_nr = 0x0104
    };

    enum IdentifyOptions{
        IP_nr = 1,
        DeviceProperties_nr = 2
    };

    enum IdentifyIPSubOptions{
        IPAdress_nr = 1,
        MACAdress_nr = 2
    };

    enum IdentifyDevicePropertiesSubOptions{
        TypeOfStation_nr = 1,
        NameOfStation_nr = 2,
        DeviceID_nr = 3,
        DeviceRole_nr = 4,
        DeviceOptions_nr = 5
    };

    struct DeviceIdentification{
        std::string MAC;
        std::string nameOfStation;
        std::string typeOfStation;
        uint16_t vendorID;
        uint16_t deviceID;
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
     * the IOCS is the Consumer status. When the PLC sends data TO a device, the PLC is a provider 
     * and the device is the consumer. The Consumer Status represents how the consumer handled the 
     * last message: it can be either good or bad. This works the same way in the opposite direction: 
     * from Device to PLC. I will not use this status information for now.
     */
    struct IOCS{
        uint16_t slot;
        uint16_t subslot;
        uint16_t offset;
    };

    struct DataDescription{
        uint16_t dataDescription; //Input or Output
        uint16_t SubmoduleDataLength;
        uint8_t IOCSLength;
        uint8_t IOPSLength;
    };

    struct Submodule{
        uint16_t subslot;
        uint32_t submoduleIdentNr;
        std::vector<DataDescription> dataDescriptions;
    };

    struct API_IO_Data{
        std::vector<IODataObject> io_data_objects;
        std::vector<IOCS> iocs_s;
    };

    struct API_Module_Info{
        std::vector<Submodule> submodules;
        uint16_t slot;
    };

    struct IOCRBlockReq{
        uint16_t iocr_type;
        std::vector<API_IO_Data> apis;
    };

    /**
     * @brief Contains API Module info, which holds the data lengths for IO-data. The 
     * data lengths together with the data offsets can be used to decode PN-IO messages. 
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
         * @brief: Gets a dataDescription from a device subslot.
         */
        DataDescription getDataDescriptionBySubslot(uint16_t slot, uint16_t subslot);
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

        /**
         * @brief: Gets amount of data descriptions a subslot has. If one subslot is
         * used both for sending and receiving by the Controller. 
         */
        uint8_t requiredDataDescriptionAmount(const uint16_t slotNr, const uint16_t subslotNr);
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
        void handleIdentify(const std::string& device_mac, std::vector<uint8_t>& data);
        std::vector<PNDevice> devices;
        std::vector<DeviceIdentification> deviceIdentifications;
        std::string PLC_MAC;

        /**
         * @brief This function gets the device interface required to decode PNIO messages. 
         * @return A vector of pairs where the first member is the data offset and the second is the data length. 
         */
        DeviceInterface getDeviceDataOffsets(const std::string& src_mac, const std::string& dst_mac);
        /**
         * @brief This function returns a device by it's MAC-address. 
         */
        std::optional<PNDevice> getDevice(std::string deviceMAC);
        /**
         * @brief This function returns a device by it's MAC-address. 
         */
        std::optional<DeviceIdentification> getDeviceIdentification(std::string deviceMAC);
        /**
         * @brief This function calls push_back on the devices vector only
         * if the device doesn't exist yet. 
         */
        void updateDevice(PNDevice device);
        /**
         * @brief This function calls push_back on the deviceIdentifications
         * only if the device doesn't exist yet.
         */
        void updateDeviceIdentification(DeviceIdentification devIdent);
    };

};

#endif