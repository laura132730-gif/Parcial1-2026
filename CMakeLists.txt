cmake_minimum_required(VERSION 3.22)

# ==============================================================================
# 1. Declaración del Proyecto
# ==============================================================================
project(Parcial1-2026 C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# ==============================================================================
# 2. Definiciones del Preprocesador (STM32F4)
# ==============================================================================
add_definitions(
    -DSTM32F401xC
    -DUSE_HAL_DRIVER
)

add_compile_options(
    -Wall
    -Wextra
    -fdata-sections
    -ffunction-sections
)

# ==============================================================================
# 3. Recolección de Fuentes (.c y .s)
# ==============================================================================
file(GLOB_RECURSE SOURCES
    "Core/Src/*.c"
    "Core/Startup/*.s"
    "Core/Startup/*.S"
    "Drivers/STM32F4xx_HAL_Driver/Src/*.c"
)

# Recopilar startup en raíz si existe ahí
file(GLOB ROOT_ASM_SOURCES "*.s" "*.S")
list(APPEND SOURCES ${ROOT_ASM_SOURCES})
list(REMOVE_DUPLICATES SOURCES)

# ==============================================================================
# 4. Directorios de Inclusión (Headers)
# ==============================================================================
include_directories(
    Core/Inc
    Drivers/STM32F4xx_HAL_Driver/Inc
    Drivers/STM32F4xx_HAL_Driver/Inc/Legacy
    Drivers/CMSIS/Device/ST/STM32F4xx/Include
    Drivers/CMSIS/Include
)

# ==============================================================================
# 5. Creación del Ejecutable Target
# ==============================================================================
add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})

# Opciones de Linker limpias (sin inyectar banderas -T duplicadas)
target_link_options(${CMAKE_PROJECT_NAME} PRIVATE
    -Wl,-Map=${CMAKE_PROJECT_NAME}.map
    -Wl,--gc-sections
    -Wl,--print-memory-usage
)

# ==============================================================================
# 6. Generación de Archivos Binarios (.hex y .bin)
# ==============================================================================
add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${CMAKE_PROJECT_NAME}> ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${CMAKE_PROJECT_NAME}> ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.bin
    COMMENT "Generando archivos binarios .hex y .bin exitosamente..."
)