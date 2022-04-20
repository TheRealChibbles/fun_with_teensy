set(CMAKE_HOST_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(TOOLCHAIN_PATH /home/chibbles/gcc-arm-none-eabi-10.3-2021.07/bin/)

set(CMAKE_AR            ${TOOLCHAIN_PATH}arm-none-eabi-ar)
set(CMAKE_ASM_COMPILER  ${TOOLCHAIN_PATH}arm-none-eabi-as)
set(CMAKE_C_COMPILER    ${TOOLCHAIN_PATH}arm-none-eabi-gcc)
set(CMAKE_LINKER        ${TOOLCHAIN_PATH}arm-none-eabi-ld)
set(CMAKE_OBJCOPY       ${TOOLCHAIN_PATH}arm-none-eabi-objcopy)
set(CMAKE_RANLIB        ${TOOLCHAIN_PATH}arm-none-eabi-ranlib)
set(CMAKE_SIZE          ${TOOLCHAIN_PATH}arm-none-eabi-size)
set(CMAKE_STRIP         ${TOOLCHAIN_PATH}arm-none-eabi-strip)


