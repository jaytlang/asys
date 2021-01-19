SRC = $(wildcard *.c)
ASRC = $(wildcard *.S)

OBJ = $(SRC:.c=.o)
AOBJ = $(ASRC:.S=.o)

DEP = $(OBJ:.o=.d)
ADEP = $(AOBJ:.o=.d)

TARGET = asyskrn.exe
MAP = asyskrn.map
LDSCRIPT = asys.ld

DSYS = dsys/dsys.a
HSYS = hsys/hsys.a
LSYS = lsys/lsys.a
MSYS = msys/msys.a
PSYS = psys/psys.a

export CC = riscv64-unknown-elf-gcc
export LD = riscv64-unknown-elf-ld
export AS = riscv64-unknown-elf-as
export AR = riscv64-unknown-elf-ar

export CFLAGS = -O2 -g -Wall -pedantic -ansi -MD -Wextra -Werror -ffreestanding
export CFLAGS += -mcmodel=medany -Ikapi/ -fno-pie
export LDFLAGS = -nostdlib -T$(LDSCRIPT) -Map=$(MAP)
export ARFLAGS = rcs

$(TARGET): $(OBJ) $(AOBJ) $(MSYS) $(DSYS) $(LSYS) $(HSYS) $(PSYS)
	@echo "	LD	$@"
	@$(LD) -o $@ $^ $(LDFLAGS)

-include $(DEP) $(ADEP)

%.o: %.S
	@echo "	AS	$<"
	$(AS) --MD $(@:.o=.d) -c -o $@ $<

%.o: %.c
	@echo "	CC	$<"
	$(CC) $(CFLAGS) -c -o $@ $<


$(DSYS) $(HSYS) $(LSYS) $(MSYS) $(PSYS):
	@$(MAKE) -C $(shell echo $@ | sed 's/\/.*//')

.PHONY: clean
clean: clean-hsys clean-dsys clean-lsys clean-msys clean-psys
	@echo "	CLEAN	$(TARGET)"
	@rm -rf $(OBJ) $(AOBJ) $(DEP) $(ADEP) $(TARGET) $(MAP)

.PHONY: clean-hsys clean-dsys clean-lsys clean-msys clean-psys
clean-hsys clean-dsys clean-lsys clean-msys clean-psys:
	@$(MAKE) -C $(subst clean-,,$@)/ clean
