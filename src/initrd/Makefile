HOSTSRC = $(wildcard *.c)
HOSTDEP = $(HOSTSRC:.c=.d)

UDIR = progs/
UPROGS = $(wildcard $(UDIR)/*.exe)

export HOSTCC = gcc
export HOSTCCFLAGS = -O2 -g -MD -pedantic -ansi
export INITRDLDFLAGS = -r -b binary

GENERATOR = generate.exe
TARGET = initrd.img
GENOUT = initrd.dat

$(TARGET): uprogs $(GENERATOR)
	@echo "	GEN	$(GENOUT)"
	@find $(UDIR) -path */*.exe | xargs ./$(GENERATOR) > /dev/null
	@echo "	LD	$(TARGET)"
	@$(LD) $(INITRDLDFLAGS) -o $@ $(GENOUT)

-include $(HOSTDEP)

$(GENERATOR): $(HOSTSRC)
	@echo "	HOSTCC 	$(GENERATOR)"
	@$(HOSTCC) $(HOSTCCFLAGS) -o $@ $^

.PHONY: uprogs
uprogs:
	@$(MAKE) -C $(UDIR)

.PHONY: clean
clean:
	@echo "	CLEAN	$(TARGET)"
	@$(RM) $(HOSTDEP) $(TARGET) $(GENERATOR) $(GENOUT)
	@$(MAKE) -C $(UDIR) clean
