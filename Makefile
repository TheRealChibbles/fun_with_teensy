# The name of the Chip on the Teensy LC, I'm working with
MCU=MKL26Z64

# the name of the linker script
MCU_LD = minified_memory_layout.ld

# The name of your project (used to name the compiled .hex file)
TARGET = bare_essentials

# configurable options
OPTIONS = -DF_CPU=48000000 

CPUARCH = cortex-m0plus

# Toolchain path
# $(ARM_TOOLCHAIN_PATH)
COMPILERPATH = ~/gcc-arm-none-eabi-10.3-2021.07/bin

# CFLAGS = compiler options for C
CFLAGS = -Wall -g -Os -mcpu=$(CPUARCH) -mthumb -MMD $(OPTIONS) -I. --specs=nano.specs -ffunction-sections -fdata-sections -nostdlib -fsingle-precision-constant

# linker options
LDFLAGS = -Os -Wl,--gc-sections,--relax,--defsym=__rtc_localtime=0  --specs=nano.specs -mcpu=$(CPUARCH) -mthumb -T$(MCU_LD)

# additional libraries to link
LIBS = -lm

# names for the compiler programs
CC = $(COMPILERPATH)/arm-none-eabi-gcc
OBJCOPY = $(COMPILERPATH)/arm-none-eabi-objcopy
SIZE = $(COMPILERPATH)/arm-none-eabi-size

# automatically create lists of the sources and objects
# TODO: this does not handle Arduino libraries yet...
C_FILES := $(wildcard *.c)
OBJS := $(C_FILES:.c=.o)

# the actual makefile rules (all .o files built by GNU make's default implicit rules)

all: $(TARGET).hex

%.hex: %.elf
	$(SIZE) $<
	$(OBJCOPY) -O ihex -R .eeprom $< $@

$(TARGET).elf: $(OBJS) 
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# compiler generated dependency info
-include $(OBJS:.o=.d)

clean:
	rm -f *.o *.d $(TARGET).elf $(TARGET).hex
