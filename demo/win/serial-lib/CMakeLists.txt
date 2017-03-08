cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

# Set project name
set(TARGET "win-serial")
set(WIN_SERIAL_LIB_TARGET ${TARGET} PARENT_SCOPE)
project(${TARGET} CXX)

# Source and header files to build
set(
    SOURCES
    "LastError.h"
    "LastError.cpp"
    "WindowsSerialPort.h"
    "WindowsSerialPort.cpp"
    "UART/BaudRate.h"
    "UART/DataBit.h"
    "UART/IUartDriver.h"
	"UART/ParityBit.h"
    "UART/StopBit.h"
)

# include the base library
include_directories(${LIB_INC})

# Export dir for include
set(WIN_SERIAL_LIB_INC ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)

# Build this as a library
add_library(${TARGET} ${SOURCES})

# link with ble-driver
target_link_libraries(${TARGET} ${LIB_TARGET})