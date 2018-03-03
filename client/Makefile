CC=gcc
CFLAGS=
EXEC=play.client
SRC= src/*
OBJ= $(SRC:.c=.o)

all: $(EXEC) clean

play.client: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

mrproper: clean
	rm -rf ./$(EXEC)

clean:
	rm -rf ./src/*.o
