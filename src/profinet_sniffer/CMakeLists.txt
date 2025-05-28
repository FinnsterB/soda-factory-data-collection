find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBTINS REQUIRED libtins)

add_executable(profinet_sniffer main.cpp decode_pn_connect.h decode_pn_connect.cpp)

# Include libtins headers
target_include_directories(profinet_sniffer PRIVATE ${LIBTINS_INCLUDE_DIRS})

# Link libtins
target_link_libraries(profinet_sniffer PRIVATE ${LIBTINS_LIBRARIES})

add_custom_command(TARGET profinet_sniffer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "Setting capabilities"
    COMMAND sudo setcap cap_net_raw,cap_net_admin=eip $<TARGET_FILE:profinet_sniffer>
)
