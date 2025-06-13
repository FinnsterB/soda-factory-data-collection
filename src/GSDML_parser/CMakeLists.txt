add_library(GSDML_parser STATIC tinyxml2.cpp tinyxml2.h)

target_include_directories(GSDML_parser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})