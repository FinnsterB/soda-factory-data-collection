#ifndef GSDML_PARSER_H
#define GSDML_PARSER_H

#include "tinyxml2.h"

#include <iostream>
#include <optional>

namespace GSDML{
    class Parser{
        public:
        Parser(std::string aPath);
        void stationDescriptionAvailable(uint16_t vendorID, uint16_t deviceID);
        void getIODataDescription(uint16_t vendorID, uint16_t deviceID, uint32_t subModuleIdentNr);
        private:
        bool matchDevice(const std::string& filePath, uint16_t vendorID, uint16_t deviceID);
        std::optional<std::string> extractIOData(const std::string& filePath, uint32_t submoduleIdentNr);
        std::string path;

    };
};

#endif