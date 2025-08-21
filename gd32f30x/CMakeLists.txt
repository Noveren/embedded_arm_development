cmake_minimum_required(VERSION 3.31)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_LIST_DIR}/gd32f30x/gcc-cortex-m4.cmake")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(VAR_COMPILE_OPTIONS
    -O2
    -g
)
set(VAR_LINK_OPTIONS
    -Wl,--print-memory-usage
)

add_subdirectory(gd32f30x)
target_compile_options(gd32f30x
    PRIVATE
    ${VAR_COMPILE_OPTIONS}
)

project(firmware
    LANGUAGES C
)

function(add_gd32f30x_executable PARAM_NAME)
    add_executable(${PARAM_NAME})
    aux_source_directory(src VAR_SOURCES)
    target_sources(${PARAM_NAME}
        PRIVATE
        ${VAR_SOURCES}
    )
    target_include_directories(${PARAM_NAME}
        PRIVATE
        src
    )
    target_compile_options(${PARAM_NAME}
        PRIVATE
        ${VAR_COMPILE_OPTIONS}
    )
    target_link_options(${PARAM_NAME}
        PRIVATE
        ${VAR_LINK_OPTIONS}
        -Wl,-Map=${CMAKE_BINARY_DIR}/${PARAM_NAME}.map
        $<TARGET_PROPERTY:gd32f30x,INTERFACE_LINK_OPTOINS>
    )
    target_link_libraries(${PARAM_NAME}
        PRIVATE
        gd32f30x
    )
    add_custom_command(TARGET ${PARAM_NAME} POST_BUILD
        COMMAND
        arm-none-eabi-objcopy -O binary
        "${PROJECT_BINARY_DIR}/${PARAM_NAME}"
        "${PROJECT_BINARY_DIR}/${PARAM_NAME}.bin"
    )
endfunction()

add_gd32f30x_executable(firmware)
