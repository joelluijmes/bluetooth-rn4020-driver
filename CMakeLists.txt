cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(ble-driver CXX)

set(
    source_list
    "lib/BluetoothLEDevice.h"
    "lib/BluetoothLEDevice.cpp"
    "lib/Drivers/RN4020Device.h"
    "lib/Drivers/RN4020Device.cpp"
    "lib/Drivers/RN4020Driver.h"
    "lib/Drivers/RN4020Driver.cpp"
    "lib/Models/BluetoothLEPeripheral.h"
    "lib/Models/CharacteristicProperty.h"
    "lib/Models/ClientCharacteristic.h"
    "lib/Models/ClientCharacteristicConfiguration.h"
    "lib/Models/MACAddress.h"
    "lib/Models/MACAddress.cpp"
    "lib/Models/ServerCharacteristic.h"
    "lib/Models/Services.h"
    "lib/Models/UUID.h"
    "lib/Models/UUID.cpp"
    "lib/Serial/DelimiterSerial.h"
    "lib/Serial/ISerial.h"
    "lib/Util/CircularBuffer.h"
)

include_directories(lib)
add_library(ble-driver ${source_list})

foreach(source IN LISTS source_list)
    get_filename_component(source_path "${source}" PATH)
    string(REPLACE "/" "\\" source_path_msvc "${source_path}")
    source_group("${source_path_msvc}" FILES "${source}")
endforeach()
