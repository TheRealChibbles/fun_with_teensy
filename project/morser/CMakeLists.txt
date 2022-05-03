project(Morser LANGUAGES C)

add_executable(morser main.c)
set_target_properties(morser PROPERTIES SUFFIX .elf)
target_link_libraries(morser teensy_lc_lib)


add_custom_command(TARGET morser
            POST_BUILD
            DEPENDS  morser.elf
            COMMAND ${CMAKE_OBJCOPY} -O ihex ${CMAKE_BINARY_DIR}/project/morser/morser.elf ${CMAKE_BINARY_DIR}/project/morser/morser.hex
            ) #-I elf32-littlearm


