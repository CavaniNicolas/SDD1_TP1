#options
CFLAGS = -Wall -Wextra -g -MMD
LIB = -lm

SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c,build/%.o,$(SRC))
DEP = $(patsubst %.o,%.d,$(OBJ))

.PHONY: all
all: bin/executable

bin/executable: $(OBJ)
	@mkdir -p $(@D)
	gcc -o $@ $^ $(LIB)
	@echo "executer avec ./bin/executable"

build/%.o: src/%.c
	@mkdir -p $(@D)
	gcc -c $< $(CFLAGS) -o $@

.PHONY: clean
clean:
	rm -rf build

.PHONY: reset
reset:
	rm -rf borrowings

-include $(DEP)
