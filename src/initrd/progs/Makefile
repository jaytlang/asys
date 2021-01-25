SRC = $(wildcard *.c)
EXC= $(SRC:.c=.exe)
DEP = $(SRC:.c=.d)

LDSCRIPT = user.ld

CFLAGS += -Xlinker -nostdlib -nostartfiles -T$(LDSCRIPT)

.PHONY: all
all: $(EXC)

$(EXC): %.exe: %.c
	@echo "	CC	$@"
	@$(CC) $(CFLAGS) -o $@ $<

-include $(DEP)

.PHONY: clean
clean:
	@echo "	CLEAN	uprogs"
	@$(RM) $(EXC) $(DEP)
