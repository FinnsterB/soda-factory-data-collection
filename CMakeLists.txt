cmake_minimum_required(VERSION 3.10)
project(MyMultiProject)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set default to Debug if nothing is specified
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

# Add subdirectories
# add_subdirectory(src/data_handler)
add_subdirectory(src/profinet_sniffer)