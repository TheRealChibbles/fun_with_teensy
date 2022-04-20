project(Morser LANGUAGES C)

add_executable(morser main.c)
set_target_properties(morser PROPERTIES SUFFIX .elf)
target_link_libraries(morser teensy_lc_lib)
