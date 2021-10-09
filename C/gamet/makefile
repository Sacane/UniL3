CC=gcc
CFLAGS=-ansi -Wall 
LDFLAGS=-lMLV
EXEC=tetris
OBJ1=main
OBJ2=linkedlist
OBJ3=ball

SRC=./src/
BIN=./bin/
INC=./includes/


$(EXEC): $(BIN)$(OBJ1).o $(BIN)$(OBJ2).o $(BIN)$(OBJ3).o
		$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f $(BIN).o

mrproper: clean
	rm -f $(EXEC)