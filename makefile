#options
CFLAGS = -Wall -Wextra -g -MMD
LIB = -lm

SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c,build/%.o,$(SRC))
DEP = $(patsubst %.o,%.d,$(OBJ))

.PHONY: all
all: bin/executable

bin/executable: $(OBJ)
	@mkdir -p $(@D) #créer le dossier bin, s'il n'existe pas
	@gcc -o $@ $^ $(LIB) #édition des liens
	@echo "executer avec ./bin/executable"

#génère les fichiers .o (dans build) à partir des fichiers .c (dans src) du même nom
build/%.o: src/%.c
	@mkdir -p $(@D) #créer le dossier build, s'il n'existe pas
	@gcc -c $< $(CFLAGS) -o $@ #compilation

.PHONY: clean
clean:
	rm -rf build

-include $(DEP)
