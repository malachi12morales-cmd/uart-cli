cmake_minimum_required(VERSION 3.22)
enable_language(C ASM)

# Symbols (no USE_HAL_DRIVER: bare metal)
# HSE_VALUE is 8 MHz because the Nucleo's clock comes from the ST-Link
set(MX_Defines_Syms
    STM32F446xx
    HSE_VALUE=8000000U
    $<$<CONFIG:Debug>:DEBUG>
)

# Include paths
set(MX_Include_Dirs
    ${CMAKE_CURRENT_SOURCE_DIR}/../../inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/CMSIS/Device/ST/STM32F4xx/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/CMSIS/Include
)

# Sources
set(MX_Application_Src
    ${CMAKE_CURRENT_SOURCE_DIR}/../../src/main.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../src/system_stm32f4xx.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../src/sysmem.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../src/syscalls.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../startup_stm32f446xx.s
)

set(MX_LINK_DIRS)
set(MX_LINK_LIBS ${TOOLCHAIN_LINK_LIBRARIES})

# Interface library for includes and symbols
add_library(stm32cubemx INTERFACE)
target_include_directories(stm32cubemx INTERFACE ${MX_Include_Dirs})
target_compile_definitions(stm32cubemx INTERFACE ${MX_Defines_Syms})

target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${MX_Application_Src})
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE ${MX_LINK_DIRS})
target_link_libraries(${CMAKE_PROJECT_NAME} ${MX_LINK_LIBS})

set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES ADDITIONAL_CLEAN_FILES ${CMAKE_PROJECT_NAME}.map)