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

    class PNConfigMsg
    {
        
    };

    class PNDevice
    {
    public:
        PNDevice(std::string aMac, std::string aName): mac(aMac), name(aName)
        {

        }
        bool isConfigured;
        std::string mac;
        std::string name;
        IOCRBlockReq input;
        IOCRBlockReq output;
        std::vector<ExpectedSubmoduleBlockReq> expectedSubmodules;


        /**
         * @brief: Reads a uint8_t from data vector.
         */
        uint8_t read8(std::vector<uint8_t>& data, uint16_t& offset){
            return data.at(offset++);
        }

        /**
         * @brief: Reads a uint16_t from data vector.
         */
        uint16_t read16(std::vector<uint8_t>& data, uint16_t& offset){
            uint16_t result = 0;
            result = data.at(offset++);
            result << 8;
            result += data.at(offset++);
            return result;
        }

        /**
         * @brief: Reads a uint32_t from data vector.
         */
        uint32_t read32(std::vector<uint8_t>& data, uint16_t& offset){
            uint32_t result = 0;
            result = data.at(offset++);
            result << 8;
            result += data.at(offset++);
            result << 8;
            result += data.at(offset++);
            result << 8;
            result += data.at(offset++);
            return result;
        }

        void parseConnectMessage(std::vector<uint8_t>& data){
            std::cout << "Payload size: "<< data.size() << std::endl;
            uint16_t offset = 0;
            offset += 80;// skip DCE/RPC data(80 bytes)
            offset += 22;// skip until ARBlockReq Blocklength
            uint16_t lengthToSkip = read16(data, offset);
            std::cout << "Skipping " << lengthToSkip << " bytes";
            offset += lengthToSkip;// skip ARBlockReq Blocklength
            offset += 44;// skip to NumberOfAPIS
            uint16_t loopAmount = read16(data, offset);
            std::cout << "Input IOCRBlockReq number of api's: " << loopAmount << " at offset " << offset << std::endl;
            for(uint16_t i = 0; i < loopAmount; i++)
            {
                offset += 4;
                uint16_t numOfIODataObjs = data.at(offset);
                numOfIODataObjs << 8;
                offset++;
                numOfIODataObjs += data.at(offset);
                offset++;
                std::cout << "Api " << i << " has: " << numOfIODataObjs << " IODataObjects" << std::endl;

                API_IO_Data api;
                for (uint16_t j = 0; j < numOfIODataObjs; j++)
                {
                    IODataObject obj;
                    obj.slot = read16(data, offset);

                    obj.subslot = read16(data, offset);

                    obj.offset = read16(data, offset);
                    api.io_data_objects.push_back(obj);
                }

                uint16_t numOfIOCS = data.at(offset);
                numOfIOCS << 8;
                offset++;
                numOfIOCS += data.at(offset);
                offset++;
                
                for (uint16_t j = 0; j < numOfIOCS; j++)
                {
                    IOCS iocs;
                    iocs.slot = read16(data, offset);

                    iocs.subslot = read16(data, offset);

                    iocs.offset = read16(data, offset);
                    api.iocs_s.push_back(iocs);
                }
                std::cout << "Parsed " << api.io_data_objects.size() << " IODataObjects." << std::endl;
                std::cout << "Parsed " << api.iocs_s.size() << " IOCS's." << std::endl;
                input.apis.push_back(api);
            }
        }
    };

};

#endif