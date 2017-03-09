cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

# Set project name
set(TARGET "win-central-browser")
project(${TARGET} CXX)

# Source and header files to build
set(
    SOURCES
    "main.cpp"
)

# Keep structure for Visual Studio
assign_source_group(${SOURCES})

# include the src; ble-driver; win-serial
include_directories(${LIB_INC} ${WIN_SERIAL_LIB_INC} ${WIN_CONSOLE_LIB_INC})

# Build this as an executable
add_executable(${TARGET} ${SOURCES})

# link with ble-driver; win-serial; console-lib
target_link_libraries(${TARGET} ${LIB_TARGET} ${WIN_SERIAL_LIB_TARGET} ${WIN_CONSOLE_LIB_TARGET})