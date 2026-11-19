# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.3.1)
set(toolchainVersion 15_2_Rel1)
set(picotoolVersion 2.3.1)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico2_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(wallreminder C CXX ASM)

set(PICO_CXX_ENABLE_EXCEPTIONS 1)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Every .cpp file in the project must be listed here
add_executable(wallreminder
        src/main.cpp
        src/core/controller.cpp
        src/drivers/buzzer.cpp
        src/drivers/pir.cpp
        src/drivers/button.cpp
        src/core/reminderqueue.cpp
        src/drivers/wifi.cpp
)

pico_set_program_name(wallreminder "wallreminder")
pico_set_program_version(wallreminder "0.1")

# printf / serial input over USB, not UART
pico_enable_stdio_uart(wallreminder 0)
pico_enable_stdio_usb(wallreminder 1)

# Libraries: standard SDK + Wi-Fi chip driver (needed for the onboard LED)
target_link_libraries(wallreminder
        pico_stdlib
        pico_cyw43_arch_lwip_poll 
        hardware_pwm
)

# Lets includes like "core/controller.h" resolve from src/
target_include_directories(wallreminder PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/src
)

pico_add_extra_outputs(wallreminder)