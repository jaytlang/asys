KERNEL = kernel/asyskrn.exe
CPUS = 4
RAM = 256M

QEMU = qemu-system-riscv64
QEMUFLAGS = -machine virt -bios none -kernel $(KERNEL)
QEMUFLAGS += -m $(RAM) -smp $(CPUS) -nographic 
QEMU_GDBFLAGS = -S -gdb tcp::9000

GDB = riscv64-unknown-elf-gdb
MAKEFLAGS = --no-print-directory --quiet

.PHONY: all
all:
	@$(MAKE) -C kernel/

$(KERNEL):
	@$(MAKE) -C kernel/

.PHONY: sim
sim: all
	@echo "	QEMU	$(KERNEL)"
	@$(QEMU) $(QEMUFLAGS)

###### Developer helpers beyond this point ######
machine.dts: all
	@echo "	DTC	$@"
	@$(QEMU) $(QEMUFLAGS) -machine dumpdtb=machine.dtb
	@dtc machine.dtb > $@
	@$(RM) machine.dtb

.PHONY: sim-debug
sim-debug: all
	@echo "	QEMU	$(KERNEL)"
	@echo "	Now make gdb and do: target remote localhost:9000"
	@$(QEMU) $(QEMUFLAGS) $(QEMU_GDBFLAGS)

.PHONY: gdb
gdb: all
	@echo "	GDB	$(KERNEL)"
	@$(GDB) $(KERNEL)

.PHONY: clean
clean:
	@$(MAKE) -C kernel/ clean
	@echo "	CLEAN	ALL"

.PHONY: format
format:
	@echo "	FORMAT	.clang-format"
	@find . -iname *.h -o -iname *.c | xargs clang-format -i	
	@find . -iname *.h -o -iname *.c | xargs sed -i 's/\ {/{/'
	@find . -iname *.h -o -iname *.c | xargs sed -i 's/}\ /}/'

