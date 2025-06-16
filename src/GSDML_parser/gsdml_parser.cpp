#include "gsdml_parser.h"

GSDML::Parser::Parser(std::string aPath)
{
}

void GSDML::Parser::stationDescriptionAvailable(uint16_t vendorID, uint16_t deviceID)
{

}

void GSDML::Parser::getIODataDescription(uint16_t vendorID, uint16_t deviceID, uint32_t subModuleIdentNr)
{

}

bool GSDML::Parser::matchDevice(const std::string &filePath, uint16_t vendorID, uint16_t deviceID)
{
    return false;
}

std::optional<std::string> GSDML::Parser::extractIOData(const std::string &filePath, uint32_t submoduleIdentNr)
{
    return std::optional<std::string>();
}