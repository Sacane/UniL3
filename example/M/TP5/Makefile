# Makefile Binary Breaker

OBJ=obj/
INC=inc/
SRC=src/

CC=gcc
CFLAGS=-ansi -Wall -g -fsanitize=address
OBJE=$(OBJ)Main.o $(OBJ)binKey.o
EXEC=$(OBJ)breaker

all: $(EXEC)

$(EXEC): $(OBJE)
	$(CC) -o $@ $^ $(OBJ)code.o $(CFLAGS)

$(OBJ)Main.o: $(SRC)Main.c $(INC)binKey.h

$(OBJ)binKey.o: $(SRC)binKey.c $(INC)binKey.h $(INC)code.h

$(OBJ)%.o:
	$(CC) -c $< $(CFLAGS) -o $@

clean:
	rm -f $(OBJ)Main.o
	rm -f $(OBJ)binKey.o
	rm -f $(EXEC)
