KERNEL = src/asyskrn.exe
CPUS = 4
RAM = 256M

QEMU = qemu-system-riscv64
QEMUFLAGS = -machine virt -bios none -kernel $(KERNEL)
QEMUFLAGS += -m $(RAM) -smp $(CPUS) -nographic 
QEMU_GDBFLAGS = -s -S

GDB = riscv64-unknown-elf-gdb

MAKEFLAGS = --no-print-directory

$(KERNEL):
	@echo "	RECURSE		$(KERNEL)"
	@$(MAKE) $(MAKEFLAGS) -C src/

.PHONY: sim
sim: $(KERNEL)
	@echo "	QEMU		$(KERNEL)"
	@$(QEMU) $(QEMUFLAGS)

.PHONY: debug
sim-debug: $(KERNEL)
	@echo "	DEBUG		$(KERNEL)"
	@echo "	Now make gdb and do: target remote localhost:1234"
	@$(QEMU) $(QEMUFLAGS) $(QEMU_GDBFLAGS)

.PHONY: gdb
gdb: $(KERNEL)
	@echo "	GDB		$(KERNEL)"
	@$(GDB) $(KERNEL)

.PHONY: clean
clean:
	@echo "	RECURSE 	$(KERNEL)"
	@$(MAKE) $(MAKEFLAGS) -C src/ clean
