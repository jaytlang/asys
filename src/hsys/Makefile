SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
DEP = $(OBJ:.o=.d)

TARGET = hsys.a
CFLAGS += -I../kapi

$(TARGET): $(OBJ)
	@echo "	AR		$@"
	@$(AR) $(ARFLAGS) $@ $^

-include $(DEP)

%.o: %.c
	@echo "	CC		$<"
	@$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	@echo "	CLEAN		$(TARGET)"
	@rm -rf $(OBJ) $(DEP) $(TARGET)

