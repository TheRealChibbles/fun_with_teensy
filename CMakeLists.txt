cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_TOOLCHAIN_FILE "/home/chibbles/fun_with_teensy/arm_none_eabi_gcc_toolchain.cmake")
#set(CMAKE_VERBOSE_MAKEFILE ON)
project(Fun_with_teensy LANGUAGES C)
add_subdirectory(project)
add_subdirectory(library)


#add_custom_target( CreateHEX ALL
#        DEPENDS ELFCreated
#        )   

#add_custom_command(
#            POST_BUILD
#            OUTPUT ELFCreated
#            DEPENDS  morser
#            COMMAND ${CMAKE_OBJCOPY}  -O ihex ${CMAKE_BINARY_DIR}/project/morser/morser.elf ${CMAKE_BINARY_DIR}/project/morser/morser.hex
#            ) #-I elf32-littlearm

#Probleme!!!!!!!
#Wenn das projekt gebaut wird nutzt es die library nicht weil das executable die main.c ist und die library nicht eingebundne wird
# Lösung: executable muss miniied startup werden welche durch die main funktion im main.c file überschrieben wird.
# ansonsten gibt es einfach nur ein hex ile mit der implementierten while schleife

#denkweise vielleicht anpassen und cmake file nach folgendem weg bauen:
#1. was wird mein microcontroller mit dem ich arbeite:
#(zu jedem mc ibt es eine library für die treiber und register stuff)
#2. welches projekt will ich laufen lassen?
# abfolge: main.c wird gebaut -> library wird gebaut (ist gebaut wenn nicht verändert) -> minified startup(das ist die executable) wird gebaut -> alles wird in den minified startup gelinked! 

#das bedeutet: das zu bauende target liegt im microcontroller ordner und bindet die main.c des projektes ein und nicht umekehrt. das zu bauende target ist minified_startup.c

#erstellung eines weiteren ordners (z.B. Core) hier gibt es dann nur die verschiedenen controller als ordner und die startup files register.h und peripheral drivers.
# im library ordner kommen nur treiber für devices rein welche von den verschiedennen microcontrollern nach bedarf genutzt werden können.
