cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(ble-framework)

add_subdirectory(ble-driver)
add_subdirectory(demo/win/serial-lib)
add_subdirectory(demo/win/advertise)
add_subdirectory(demo/win/central)