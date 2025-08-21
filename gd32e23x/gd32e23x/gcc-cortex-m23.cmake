cmake_minimum_required(VERSION 3.31)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR ARM)
set(VAR_TOOLCHAIN_PREFIX "arm-none-eabi-")

set(CMAKE_C_COMPILER "${VAR_TOOLCHAIN_PREFIX}gcc")
set(CMAKE_CXX_COMPILER "${VAR_TOOLCHAIN_PREFIX}g++")
set(CMAKE_ASM_COMPILER "${CMAKE_C_COMPILER}")
set(CMAKE_AR "${VAR_TOOLCHAIN_PREFIX}gcc-ar")
set(CMAKE_RANLIB "${VAR_TOOLCHAIN_PREFIX}gcc-ranlib")
set(CMAKE_LINKER "${CMAKE_C_COMPILER}")

execute_process(
    COMMAND ${CMAKE_C_COMPILER} -print-sysroot
    OUTPUT_VARIABLE VAR_SYSROOT OUTPUT_STRIP_TRAILING_WHITESPACE
)
set(CMAKE_SYSROOT ${VAR_SYSROOT})
set(VAR_CORTEX_CM23_OPTIONS
    -mcpu=cortex-m23
    -march=armv8-m.base
    -mthumb
    -mfloat-abi=soft
    -specs=nano.specs

    # -specs=nosys.specs
    # -nostdlib
)
add_compile_options(
    -isystem ${VAR_SYSROOT}/include
    ${VAR_CORTEX_CM23_OPTIONS}
    -ffunction-sections
    -fdata-sections
)
add_link_options(
    ${VAR_CORTEX_CM23_OPTIONS}
    -Wl,-e Reset_Handler
    -Wl,--gc-sections
)