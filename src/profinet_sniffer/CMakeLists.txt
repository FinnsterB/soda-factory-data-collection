find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBTINS REQUIRED libtins)

add_executable(profinet_sniffer main.cpp decode_pn_connect.h)

# Include libtins headers
target_include_directories(profinet_sniffer PRIVATE ${LIBTINS_INCLUDE_DIRS})

# Link libtins
target_link_libraries(profinet_sniffer PRIVATE ${LIBTINS_LIBRARIES})
