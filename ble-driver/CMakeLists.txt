cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

# Set project name
set(TARGET "ble-driver")
set(LIB_TARGET ${TARGET} PARENT_SCOPE)
project(${TARGET} CXX)

# Source and header files to build
set(
    SOURCES
    "src/BluetoothLEDevice.h"
    "src/BluetoothLEDevice.cpp"
    "src/Drivers/RN4020Device.h"
    "src/Drivers/RN4020Device.cpp"
    "src/Drivers/RN4020Driver.h"
    "src/Drivers/RN4020Driver.cpp"
    "src/Models/BluetoothLEPeripheral.h"
    "src/Models/CharacteristicProperty.h"
    "src/Models/ClientCharacteristic.h"
    "src/Models/ClientCharacteristicConfiguration.h"
    "src/Models/MACAddress.h"
    "src/Models/MACAddress.cpp"
    "src/Models/ServerCharacteristic.h"
    "src/Models/Services.h"
    "src/Models/UUID.h"
    "src/Models/UUID.cpp"
    "src/Serial/DelimiterSerial.h"
    "src/Serial/ISerial.h"
    "src/Util/CircularBuffer.h"
)

# include the src and base library
include_directories("src")

# Export dir for include
set(LIB_INC ${CMAKE_CURRENT_SOURCE_DIR}/src PARENT_SCOPE)

# Build this as a library
add_library(${TARGET} ${SOURCES})
