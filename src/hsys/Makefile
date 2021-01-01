SRC = $(wildcard *.c)
ASRC = $(wildcard *.S)

OBJ = $(SRC:.c=.o)
AOBJ = $(ASRC:.S=.o)
DEP = $(OBJ:.o=.d)
ADEP = $(AOBJ:.o=.d)

TARGET = hsys.a
CFLAGS += -I../kapi

$(TARGET): $(OBJ) $(AOBJ)
	@echo "	AR	$@"
	@$(AR) $(ARFLAGS) $@ $^

-include $(DEP) $(ADEP)

%.o: %.c
	@echo "	CC	$<"
	@$(CC) $(CFLAGS) -c -o $@ $<
%.o: %.S
	@echo "	AS	$<"
	@$(AS) --MD $(@:.o=.d) -c -o $@ $<

.PHONY: clean
clean:
	@echo "	CLEAN	$(TARGET)"
	@rm -rf $(OBJ) $(AOBJ) $(DEP) $(ADEP) $(TARGET)

