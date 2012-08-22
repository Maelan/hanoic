CC=gcc
LDFLAGS=-lncurses -lpthread
# -lmingw32 => needed under Windows
CFLAGS=-W -Wall -Wextra -pedantic -std=c1x
SRC= $(wildcard src/*.c)
OBJ= $(SRC:src/%.c=obj/%.o)
EXEC=hanoic

all: $(EXEC)

$(EXEC): $(OBJ)
	@echo "====	Édition des liens ($^)"
	$(CC) -o "$@" $^ $(LDFLAGS)

obj/%.o: src/%.c
	@echo "====	Compilation de '$<' ($?)"
	$(CC) -o "$@" -c "$<" $(CFLAGS)


##### VARIABLES INTERNES #####
# $@		cible
# $^		dépendances
# $<		1ère dépendance
# $?		dépendances + récentes que la cible
# $*		fichier sans suffixe
