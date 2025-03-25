# The following variables contains the files used by the different stages of the build process.
set(BTL_HoangTrungAn_default_default_XC8_FILE_TYPE_assemble)
set_source_files_properties(${BTL_HoangTrungAn_default_default_XC8_FILE_TYPE_assemble} PROPERTIES LANGUAGE ASM)
set(BTL_HoangTrungAn_default_default_XC8_FILE_TYPE_assemblePreprocess)
set_source_files_properties(${BTL_HoangTrungAn_default_default_XC8_FILE_TYPE_assemblePreprocess} PROPERTIES LANGUAGE ASM)
set(BTL_HoangTrungAn_default_default_XC8_FILE_TYPE_compile
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../BUZZER.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../I2C_LCD.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../UART.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../build/CMakeFiles/3.28.1/CompilerIdC/CMakeCCompilerId.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../main.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../software_PWM.c")
set_source_files_properties(${BTL_HoangTrungAn_default_default_XC8_FILE_TYPE_compile} PROPERTIES LANGUAGE C)
set(BTL_HoangTrungAn_default_default_XC8_FILE_TYPE_link)

# The (internal) path to the resulting build image.
set(BTL_HoangTrungAn_default_internal_image_name "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/BTL_HoangTrungAn/default/default.elf")

# The name of the resulting image, including namespace for configuration.
set(BTL_HoangTrungAn_default_image_name "BTL_HoangTrungAn_default_default.elf")

# The name of the image, excluding the namespace for configuration.
set(BTL_HoangTrungAn_default_original_image_name "default.elf")

# The output directory of the final image.
set(BTL_HoangTrungAn_default_output_dir "${CMAKE_CURRENT_SOURCE_DIR}/../../../out/BTL_HoangTrungAn")
