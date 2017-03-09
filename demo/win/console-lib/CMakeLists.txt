cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

# Set project name
set(TARGET "win-console")
set(WIN_CONSOLE_LIB_TARGET ${TARGET} PARENT_SCOPE)
project(${TARGET} CXX)

# Source and header files to build
set(
    SOURCES
	"ConsoleMenu.h"
	"ConsoleMenu.cpp"
)
# Keep structure for Visual Studio
assign_source_group(${SOURCES})

# Export dir for include
set(WIN_CONSOLE_LIB_INC ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)

# Build this as a library
add_library(${TARGET} ${SOURCES})
