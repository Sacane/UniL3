CC=gcc
CFLAGS=-ansi -Wall -lreadline 
EXEC= mycalc
OBJ1= main.o
OBJ2= operator.o
OBJ3= stack.o
OBJ4= opt.o

SRC=./src/
BIN=./bin/
INC=./includes/

$(EXEC): $(BIN)$(OBJ1) $(BIN)$(OBJ2) $(BIN)$(OBJ3) $(BIN)$(OBJ4)
		$(CC) -o $@ $^ $(CFLAGS)

$(BIN)$(OBJ2): $(INC)operator.h 
		$(CC) -o $@ -c $(SRC)operator.c $(CFLAGS) -lm

$(BIN)$(OBJ3):$(INC)stack.h 
		$(CC) -o $@ -c $(SRC)stack.c $(CFLAGS)

$(BIN)$(OBJ4):$(INC)opt.h $(INC)operator.h $(INC)stack.h
		$(CC) -o $@ -c $(SRC)opt.c $(CFLAGS)

$(BIN)$(OBJ1): $(SRC)main.c $(INC)opt.h
		$(CC) -o $@ -c $(SRC)main.c $(CFLAGS)	


clean:
		rm -f $(BIN)*.o 

mrproper: clean
		rm -f $(EXEC)