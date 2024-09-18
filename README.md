# CMake file template for custom library in STM32 VSCode extension
This is a template to add a custom library directory containing .c and .h in a STM32 project.
The template contains template of CMakeLists.txt in `modules` directory and enabling float printf('-u _printf_float').

## Dependencies
- Visual Studio Code
- STM32 VS Code Extension
- STM32 Cube MX 6.12.0
- STM32 Cube CLT 1.16.0

## Project tree
```
VENTA_TEMPLATE/
├── stm32cubemx/
│   ├── CMakeLists.txt
├── Core/
│   ├── Inc/
│   │   └── main.h
│   ├── Src/
│       └── main.c
├── Drivers/
├── modules/        <--- Custom directory
│   ├── inc/        <--- Header files directory
│   │   └── ui.h
│   │   └── myLib.h
│   ├── src/        <--- Sources files directory
│   │   └── ui.c
│   │   └── myLib.c
│   └── CMakeLists.txt
├── CMakeLists.txt
```

## VENTA_TEMPLATE/modules/CMakeLists.txt
CMakeLists.txt files for `modules` directory.
```
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
```
## VENTA_TEMPLATE/CMakeLists.txt
CMakeLists.txt files for the project directory.
```
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


# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME VENTA_Template)

# Include toolchain file
include("cmake/gcc-arm-none-eabi.cmake")

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Enable CMake support for ASM and C languages
enable_language(C ASM)

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME})

# Add STM32CubeMX generated sources
add_subdirectory(cmake/stm32cubemx)

# Add modules library
add_subdirectory(modules)

# Link options setup
target_link_options(${CMAKE_PROJECT_NAME} PRIVATE
    -u _printf_float        # to print float values
)

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths
)

# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user sources here
)

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined include paths
    Core/Inc
)

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined symbols
)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx
    modules         # Link modules library
    # Add user defined libraries
)

```
