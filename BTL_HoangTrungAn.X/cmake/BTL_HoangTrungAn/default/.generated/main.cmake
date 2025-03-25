include("${CMAKE_CURRENT_LIST_DIR}/rule.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/file.cmake")

set(BTL_HoangTrungAn_default_library_list )

# Handle files with suffix (s|as|asm|AS|ASM|As|aS|Asm), for group default-XC8
if(BTL_HoangTrungAn_default_default_XC8_FILE_TYPE_assemble)
add_library(BTL_HoangTrungAn_default_default_XC8_assemble OBJECT ${BTL_HoangTrungAn_default_default_XC8_FILE_TYPE_assemble})
    BTL_HoangTrungAn_default_default_XC8_assemble_rule(BTL_HoangTrungAn_default_default_XC8_assemble)
    list(APPEND BTL_HoangTrungAn_default_library_list "$<TARGET_OBJECTS:BTL_HoangTrungAn_default_default_XC8_assemble>")
endif()

# Handle files with suffix S, for group default-XC8
if(BTL_HoangTrungAn_default_default_XC8_FILE_TYPE_assemblePreprocess)
add_library(BTL_HoangTrungAn_default_default_XC8_assemblePreprocess OBJECT ${BTL_HoangTrungAn_default_default_XC8_FILE_TYPE_assemblePreprocess})
    BTL_HoangTrungAn_default_default_XC8_assemblePreprocess_rule(BTL_HoangTrungAn_default_default_XC8_assemblePreprocess)
    list(APPEND BTL_HoangTrungAn_default_library_list "$<TARGET_OBJECTS:BTL_HoangTrungAn_default_default_XC8_assemblePreprocess>")
endif()

# Handle files with suffix [cC], for group default-XC8
if(BTL_HoangTrungAn_default_default_XC8_FILE_TYPE_compile)
add_library(BTL_HoangTrungAn_default_default_XC8_compile OBJECT ${BTL_HoangTrungAn_default_default_XC8_FILE_TYPE_compile})
    BTL_HoangTrungAn_default_default_XC8_compile_rule(BTL_HoangTrungAn_default_default_XC8_compile)
    list(APPEND BTL_HoangTrungAn_default_library_list "$<TARGET_OBJECTS:BTL_HoangTrungAn_default_default_XC8_compile>")
endif()

add_executable(${BTL_HoangTrungAn_default_image_name} ${BTL_HoangTrungAn_default_library_list})

target_link_libraries(${BTL_HoangTrungAn_default_image_name} PRIVATE ${BTL_HoangTrungAn_default_default_XC8_FILE_TYPE_link})

# Add the link options from the rule file.
BTL_HoangTrungAn_default_link_rule(${BTL_HoangTrungAn_default_image_name})


# Post build target to copy built file to the output directory.
add_custom_command(TARGET ${BTL_HoangTrungAn_default_image_name} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E make_directory ${BTL_HoangTrungAn_default_output_dir}
                    COMMAND ${CMAKE_COMMAND} -E copy ${BTL_HoangTrungAn_default_image_name} ${BTL_HoangTrungAn_default_output_dir}/${BTL_HoangTrungAn_default_original_image_name}
                    BYPRODUCTS ${BTL_HoangTrungAn_default_output_dir}/${BTL_HoangTrungAn_default_original_image_name})
