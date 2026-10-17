# 01 - GPIO

## Goal
Turn on the NUCLEO-L412RB-P user LED using direct register access.

## Hardware
- NUCLEO-L412RB-P
- LD4 user LED
- LD4 connected to PB13, active-high

## Registers
- RCC_AHB2ENR - enable GPIOB clock
- GPIOB_MODER - configure PB13 as output
- GPIOB_ODR - drive PB13 high

## Build flow
main.c + startup.c
→ ARM object files
→ linker.ld
→ firmware.elf
→ firmware.bin
→ ST-Link flash

## What I learned
- Peripheral vs register vs pin
- Memory-mapped I/O
- Base address + register offset
- Bit masking and read-modify-write
- volatile register access
- Cross compilation
- .text / .data / .bss
- Vector table and Reset_Handler
- Basic linker script
- Flashing through ST-Link

## Issues
- ST-Link initially required fixing Linux udev permissions.
- Firmware required a reset after flashing before verifying LED behavior.

## TODO
- Complete exception vector table and default handlers.
- Add Makefile.


//compilation commands 
1) compile main
arm-none-eabi-gcc \
    -mcpu=cortex-m4 \
    -mthumb \
    -std=c11 \
    -Wall \
    -Wextra \
    -O0 \
    -g3 \
    -ffreestanding \
    -c src/main.c \
    -o build/main.o


2) compile startup 
arm-none-eabi-gcc \
    -mcpu=cortex-m4 \
    -mthumb \
    -std=c11 \
    -Wall \
    -Wextra \
    -O0 \
    -g3 \
    -ffreestanding \
    -c src/startup.c \
    -o build/startup.o


3) manual linkeg
arm-none-eabi-gcc \
    -mcpu=cortex-m4 \
    -mthumb \
    -nostdlib \
    -T linker.ld \
    build/startup.o \
    build/main.o \
    -Wl,-Map=build/firmware.map \
    -o build/firmware.elf