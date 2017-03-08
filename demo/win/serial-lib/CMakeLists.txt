cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

# Set project name
set(TARGET "win-serial")
set(WIN_SERIAL_LIB_TARGET ${TARGET} PARENT_SCOPE)
project(${TARGET} CXX)

# Source and header files to build
set(
    SOURCES
    "src/LastError.h"
    "src/LastError.cpp"
    "src/WindowsSerialPort.h"
    "src/WindowsSerialPort.cpp"
    "src/UART/BaudRate.h"
    "src/UART/DataBit.h"
    "src/UART/IUartDriver.h"
	"src/UART/ParityBit.h"
    "src/UART/StopBit.h"
)

# include the src and base library
include_directories("src" ${LIB_INC})

# Export dir for include
set(WIN_SERIAL_LIB_INC ${CMAKE_CURRENT_SOURCE_DIR}/src PARENT_SCOPE)

# Build this as a library
add_library(${TARGET} ${SOURCES})

# link with ble-driver
target_link_libraries(${TARGET} ${LIB_TARGET})