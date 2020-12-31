SRC = $(wildcard *.c)
ASRC = $(wildcard *.S)

OBJ = $(SRC:.c=.o)
AOBJ = $(ASRC:.S=.o)

DEP = $(OBJ:.o=.d)
ADEP = $(AOBJ:.o=.d)

TARGET = asyskrn.exe
LDSCRIPT = asys.ld

export CC = riscv64-unknown-elf-gcc
export LD = riscv64-unknown-elf-ld
export AS = riscv64-unknown-elf-as

export CFLAGS = -O2 -g -Wall -pedantic -ansi -MD -Wextra -Werror -ffreestanding
export CFLAGS += -mcmodel=medany
export ASFLAGS += --MD $(@:.o=.d)
export LDFLAGS += -nostdlib -T$(LDSCRIPT)

$(TARGET): $(OBJ) $(AOBJ)
	@echo "	LD		$@"
	@$(LD) -o $@ $^ $(LDFLAGS)

%.o: %.S
	@echo "	AS		$<"
	@$(AS) $(ASFLAGS) -c -o $@ $<

%.o: %.c
	@echo "	CC		$<"
	@$(CC) $(CFLAGS) -c -o $@ $<

-include $(DEP) $(ADEP)

.PHONY: clean
clean:
	@echo "	CLEAN		$(TARGET)"
	@rm -rf $(OBJ) $(AOBJ) $(DEP) $(ADEP) $(TARGET)

