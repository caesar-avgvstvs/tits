BUILD := build
SRC := main.c
LINKER_SRC := ../link.ld
.PHONY: main.elf main.bin

CC := riscv-none-elf-gcc
OBJCOPY := riscv-none-elf-objcopy
CFLAGS := -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized
LDFLAGS := -T $(LINKER_SRC) -nostartfiles -Xlinker --gc-sections -Wl,-Map,"$(BUILD)/CH32V203.map" --specs=nano.specs --specs=nosys.specs

all: main.elf main.bin

main.elf:
	$(CC) $(CFLAGS) $(LDFLAGS) $(SRC) -o main.elf

main.bin: main.elf
	$(OBJCOPY) -O binary $< $@
