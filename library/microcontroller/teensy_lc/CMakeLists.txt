project(Teensy_lc LANGUAGES C)

add_subdirectory(peripheral_drivers)
add_library(teensy_lc_lib INTERFACE)
target_sources(teensy_lc_lib INTERFACE ${CMAKE_CURRENT_LIST_DIR}/register.h ${CMAKE_CURRENT_LIST_DIR}/minified_startup.c)


target_link_options(teensy_lc_lib INTERFACE
-Os -Wl,--gc-sections,--relax,--defsym=__rtc_localtime=0  --specs=nano.specs -mcpu=cortex-m0plus -mthumb -T${CMAKE_CURRENT_LIST_DIR}/minified_memory_layout.ld)