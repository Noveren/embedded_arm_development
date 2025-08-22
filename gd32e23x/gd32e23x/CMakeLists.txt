# Usage:
# 1. Copy the directory to your project.
# 2. Import the toolchain and add the directory `as subdirectory`
# ```cmake
# set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_LIST_DIR}/gd32e23x/gcc-cortex-m23.cmake")
#
# add_subdirectory(gd32e23x)
# target_compile_options(gd32e23x PRIVATE -O2 -g)
# ```
# 3. Import the link options from subdirectory for your executable.
# ```
# target_link_options(your_executable PRIVATE $<TARGET_PROPERTY:gd32e23x,INTERFACE_LINK_OPTOINS>)
# ```
# TODO gd32e23x.h: HXTAL_VALUE, IRC8M_VALUE, ....
cmake_minimum_required(VERSION 3.22)

project(
    gd32e23x
    LANGUAGES C ASM
)

set(DEVICE "UNKNOWN" CACHE STRING "GD32E230K8T6")

if(DEVICE STREQUAL "GD32E230K8T6")
    set(VAR_STARTUP "${CMAKE_CURRENT_LIST_DIR}/startup_gd32e230k8t6.S")
    set(VAR_LINKER_SCRIPT "${CMAKE_CURRENT_LIST_DIR}/linker_gd32e230k8t6.ld")
else()
    message(FATAL_ERROR "Please select the specific device. GD32E230K8T6")
endif()

option(GD32E23X_USE_ADC "" OFF)
option(GD32E23X_USE_CMP "" OFF)
option(GD32E23X_USE_CRC "" OFF)
option(GD32E23X_USE_DBG "" OFF)
option(GD32E23X_USE_DMA "" OFF)
option(GD32E23X_USE_EXTI "" OFF)
option(GD32E23X_USE_FWDGT "" OFF)
option(GD32E23X_USE_GPIO "" OFF)
option(GD32E23X_USE_I2C "" OFF)
option(GD32E23X_USE_PMU "" OFF)
option(GD32E23X_USE_RTC "" OFF)
option(GD32E23X_USE_SPI "" OFF)
option(GD32E23X_USE_SYSCFG "" OFF)
option(GD32E23X_USE_TIMER "" OFF)
option(GD32E23X_USE_USART "" OFF)
option(GD32E23X_USE_WWDGT "" OFF)

configure_file(${CMAKE_CURRENT_LIST_DIR}/gd32e23x_libopt.h.in ${CMAKE_BINARY_DIR}/gd32e23x_libopt.h)

add_library(gd32e23x STATIC)
target_link_options(gd32e23x
    INTERFACE
    -Wl,-e Reset_Handler
    -Wl,--gc-sections
    -Wl,-T${VAR_LINKER_SCRIPT}
)
target_compile_definitions(gd32e23x
    PUBLIC
    GD32E23x
)
target_include_directories(gd32e23x
    PUBLIC
    ${CMAKE_BINARY_DIR}
    ${CMAKE_CURRENT_LIST_DIR}
    cmsis
    peripheral/inc
)
aux_source_directory(peripheral/src VAR_SOURCES)
target_sources(gd32e23x
    PRIVATE
    ${VAR_STARTUP}
    system_gd32e23x.c
    ${VAR_SOURCES}
)
