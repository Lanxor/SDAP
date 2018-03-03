CC=gcc
CFLAGS=
EXEC=play.server
SRC= src/*
OBJ= $(SRC:.c=.o)

all: $(EXEC) clean

play.server: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

mrproper: clean
	rm -rf ./registre.account
	rm -rf ./repertory/*
	rm -rf ./$(EXEC)

clean:
	rm -rf ./src/*.o
