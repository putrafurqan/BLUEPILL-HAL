cmake_minimum_required(VERSION 3.22)

#
# This file is generated only once,
# and is not re-generated if converter is called multiple times.
#
# User is free to modify the file as much as necessary
#

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

# Enable C++ standard (e.g., C++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME Bluepill-HAL)

# Include toolchain file
include("cmake/gcc-arm-none-eabi.cmake")

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Enable CMake support for ASM, C, and C++ languages
enable_language(C ASM CXX)

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME})

# Add STM32CubeMX generated sources
add_subdirectory(cmake/stm32cubemx)

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths
)

# Find all .cpp and .h files in KRAI_HAL_library folder and add them
file(GLOB_RECURSE KRAI_HAL_SOURCES
    "${CMAKE_SOURCE_DIR}/KRAI_HAL_library/**/*.cpp"
)

file(GLOB_RECURSE KRAI_HAL_HEADERS
    "${CMAKE_SOURCE_DIR}/KRAI_HAL_library/**/*.h"
)

# Add the mainProgram.cpp from Main folder
list(APPEND KRAI_HAL_SOURCES
    "${CMAKE_SOURCE_DIR}/Main/mainProgram.cpp"
)

# Add sources to executable (C and C++ sources)
target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${KRAI_HAL_SOURCES})

# Add include directories (for the .h files)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    "${CMAKE_SOURCE_DIR}/KRAI_HAL_library",
    "${CMAKE_SOURCE_DIR}/Main"
)

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined symbols
)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx

    # Add user defined libraries
)
