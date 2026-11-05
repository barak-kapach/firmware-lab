CC = arm-none-eabi-gcc
SIZE = arm-none-eabi-size

CPUFLAGS = -mcpu=cortex-m4 -mthumb

CFLAGS = $(CPUFLAGS) \
         -O0 \
         -g \
         -Wall \
         -Wextra \
         -ffreestanding

LDFLAGS = $(CPUFLAGS) \
          -nostdlib \
          -T linker.ld \
          -Wl,-Map=build/firmware.map

BUILD = build

OBJS = $(BUILD)/main.o \
       $(BUILD)/startup.o

all: $(BUILD)/firmware.elf

$(BUILD):
	mkdir -p $(BUILD)

$(BUILD)/main.o: src/main.c | $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/startup.o: src/startup.c | $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/firmware.elf: $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $@
	$(SIZE) $@

clean:
	rm -rf $(BUILD)