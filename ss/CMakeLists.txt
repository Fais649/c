cmake_minimum_required(VERSION 3.10)

# Project name
project(ss C)

# Set the C standard
set(CMAKE_C_STANDARD 99)

# Include directories
include_directories(include lib/libui)

# Source files
set(SRC_FILES src/main.c)

# Add the executable
add_executable(ss ${SRC_FILES})

# Link the libraries (assuming libui is compiled as a static library)
add_library(libui STATIC IMPORTED)
set_target_properties(libui PROPERTIES
    IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/libui/libui.a
)
target_link_libraries(ss libui)

