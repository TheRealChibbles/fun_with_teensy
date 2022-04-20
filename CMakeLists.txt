cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_TOOLCHAIN_FILE "/home/chibbles/fun_with_teensy/arm_none_eabi_gcc_toolchain.cmake")
project(Fun_with_teensy LANGUAGES C)
add_subdirectory(project)
add_subdirectory(library)


