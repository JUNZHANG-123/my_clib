cmake_minimum_required(VERSION 3.0)

project(bluez-gatt)

include_directories(includes)
include_directories(includes/src/shared)
include_directories(includes/lib)
include_directories(./)

add_subdirectory(libbluetooth)
add_subdirectory(libshared)

# btgatt-client
add_executable(btgatt-client
    btgatt-client.c)

target_link_libraries(btgatt-client bluetooth shared)

add_executable(pp-gattc
    pp_bt_gattc.c pp_bt_scan.c pp_wifi_ap.c pp_tcp_server.c)
target_link_libraries(pp-gattc bluetooth shared pthread)

# btgatt-server
add_executable(btgatt-server
    btgatt-server.c)

target_link_libraries(btgatt-server bluetooth shared)


# thingy.c
add_executable(thingy
    thingy.c)

target_link_libraries(thingy bluetooth shared)

install(TARGETS pp-gattc DESTINATION bin)
install(TARGETS btgatt-client DESTINATION bin)
install(TARGETS btgatt-server DESTINATION bin)
install(TARGETS thingy DESTINATION bin)
