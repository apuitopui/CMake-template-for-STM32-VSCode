###############################################################################
# CMakeLists.txt for custom library
#
# This is a template CMakeLists.txt to add a directory of custom .h and .c
###############################################################################
cmake_minimum_required(VERSION 3.22)

# Enable CMake support for ASM and C languages
enable_language(C ASM)

# project settings
project(modules)

# Find all .c file in the src directory
file(GLOB MODULE_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
)

# Create a static library for modules containing all custom .c in src directory
add_library(modules STATIC ${MODULE_SOURCES} )

# Link directory setup
target_include_directories(modules PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/inc # Add modules/inc to the include directories
    ${CMAKE_SOURCE_DIR}/Core/Inc    # Add Core/Inc to the include directories
)

# Link the stm32cubemx library to access stm driver files
target_link_libraries(modules PUBLIC
    stm32cubemx
)