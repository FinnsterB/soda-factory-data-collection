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
        PNDevice(std::string aMac, std::string aName): mac(aMac), name(aName)
        {

        }
        bool isConfigured;
        std::string mac;
        std::string name;
        IOCRBlockReq input;
        IOCRBlockReq output;
        std::vector<ExpectedSubmoduleBlockReq> expectedSubmodules;
        void parseConnectMessage(std::vector<uint8_t>& data){
            std::cout << "Payload size: "<< data.size() << std::endl;
            uint16_t offset = 0;
            offset += 80;// skip DCE/RPC data(80 bytes)
            offset += 22;// skip until ARBlockReq Blocklength
            uint16_t lengthToSkip = data.at(offset);// read length
            lengthToSkip << 8;
            offset++;
            lengthToSkip += data.at(offset);
            offset++;
            std::cout << "Skipping " << lengthToSkip << " bytes";
            offset += lengthToSkip;// skip ARBlockReq Blocklength
            offset += 44;// skip to NumberOfAPIS
            uint16_t loopAmount = data.at(offset);
            offset++;
            loopAmount << 8;
            loopAmount += data.at(offset);// loopAmount has number of API's
            offset++;
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
                    obj.slot = data.at(offset);
                    offset++;
                    obj.slot << 8;
                    obj.slot += data.at(offset);
                    offset++;

                    obj.subslot = data.at(offset);
                    offset++;
                    obj.subslot << 8;
                    obj.subslot += data.at(offset);
                    offset++;

                    obj.offset = data.at(offset);
                    offset++;
                    obj.offset << 8;
                    obj.offset += data.at(offset);
                    offset++;
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
                    iocs.slot = data.at(offset);
                    offset++;
                    iocs.slot << 8;
                    iocs.slot += data.at(offset);
                    offset++;

                    iocs.subslot = data.at(offset);
                    offset++;
                    iocs.subslot << 8;
                    iocs.subslot += data.at(offset);
                    offset++;

                    iocs.offset = data.at(offset);
                    offset++;
                    iocs.offset << 8;
                    iocs.offset += data.at(offset);
                    offset++;
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