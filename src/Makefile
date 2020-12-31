SRC = $(wildcard *.c)
ASRC = $(wildcard *.S)

OBJ = $(SRC:.c=.o)
AOBJ = $(ASRC:.S=.o)

DEP = $(OBJ:.o=.d)
ADEP = $(AOBJ:.o=.d)

TARGET = asyskrn.exe
LDSCRIPT = asys.ld

DSYS = dsys/dsys.a
HSYS = hsys/hsys.a

export CC = riscv64-unknown-elf-gcc
export LD = riscv64-unknown-elf-ld
export AS = riscv64-unknown-elf-as
export AR = riscv64-unknown-elf-ar

export CFLAGS = -O0 -g -Wall -pedantic -ansi -MD -Wextra -Werror -ffreestanding
export CFLAGS += -mcmodel=medany -Ikapi/ -fno-pie
export ASFLAGS += --MD $(@:.o=.d)
export LDFLAGS = -nostdlib -T$(LDSCRIPT)
export ARFLAGS = rcs

$(TARGET): $(OBJ) $(AOBJ) $(DSYS) $(HSYS)
	@echo "	LD		$@"
	@$(LD) -o $@ $^ $(LDFLAGS)

-include $(DEP) $(ADEP)

%.o: %.S
	@echo "	AS		$<"
	@$(AS) $(ASFLAGS) -c -o $@ $<

%.o: %.c
	@echo "	CC		$<"
	@$(CC) $(CFLAGS) -c -o $@ $<


$(DSYS) $(HSYS):
	@echo "	RECURSE		$@"
	@$(MAKE) $(MAKEFLAGS) -C $(shell echo $@ | sed 's/\/.*//')

.PHONY: clean
clean: clean-hsys clean-dsys
	@echo "	CLEAN		$(TARGET)"
	@rm -rf $(OBJ) $(AOBJ) $(DEP) $(ADEP) $(TARGET)

.PHONY: clean-hsys clean-dsys
clean-hsys clean-dsys:
	@echo "	RECURSE		$@"
	@$(MAKE) $(MAKEFLAGS) -C $(subst clean-,,$@)/ clean
