cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

# Set project name
set(TARGET "ble-driver")
set(LIB_TARGET ${TARGET} PARENT_SCOPE)
project(${TARGET} CXX)

# Source and header files to build
set(
    SOURCES
    "BluetoothLEDevice.h"
    "BluetoothLEDevice.cpp"
    "Drivers/RN4020Device.h"
    "Drivers/RN4020Device.cpp"
    "Drivers/RN4020Driver.h"
    "Drivers/RN4020Driver.cpp"
    "Models/BluetoothLEPeripheral.h"
    "Models/CharacteristicProperty.h"
    "Models/ClientCharacteristic.h"
    "Models/ClientCharacteristicConfiguration.h"
    "Models/MACAddress.h"
    "Models/MACAddress.cpp"
    "Models/ServerCharacteristic.h"
    "Models/Services.h"
    "Models/UUID.h"
    "Models/UUID.cpp"
    "Serial/DelimiterSerial.h"
    "Serial/ISerial.h"
    "Util/CircularBuffer.h"
)

# Keep structure for Visual Studio
assign_source_group(${SOURCES})

# Export dir for include
set(LIB_INC ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)

# Build this as a library
add_library(${TARGET} ${SOURCES})
