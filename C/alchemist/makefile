CC=gcc
CFLAGS=-ansi -Wall 
LDFLAGS=-lMLV
EXEC=alchemist

OBJ1=main
OBJ2=linkedlist
OBJ3=ball
OBJ4=game_logic
OBJ5=score
OBJ6=board
OBJ7=test

SRC=./src/
BIN=./bin/
INC=./includes/


$(EXEC): $(BIN)$(OBJ1).o $(BIN)$(OBJ3).o $(BIN)$(OBJ4).o $(BIN)$(OBJ5).o $(BIN)$(OBJ6).o $(BIN)$(OBJ7).o
		$(CC) -o $@ $^ $(CFLAGS) -lm

$(BIN)$(OBJ3).o: $(INC)$(OBJ3).h
		$(CC) -o $@ -c $(SRC)$(OBJ3).c $(CFLAGS)

$(BIN)$(OBJ4).o: $(INC)$(OBJ4).h $(INC)$(OBJ6).h
		$(CC) -o $@ -c $(SRC)$(OBJ4).c $(CFLAGS)

$(BIN)$(OBJ5).o: $(INC)$(OBJ5).h $(INC)$(OBJ3).h
		$(CC) -o $@ -c $(SRC)$(OBJ5).c $(CFLAGS) 

$(BIN)$(OBJ6).o: $(INC)$(OBJ6).h $(INC)$(OBJ3).h
		$(CC) -o $@ -c $(SRC)$(OBJ6).c $(CFLAGS)

$(BIN)$(OBJ7).o: $(INC)$(OBJ7).h $(INC)$(OBJ4).h
		$(CC) -o $@ -c $(SRC)$(OBJ7).c $(CFLAGS)

$(BIN)$(OBJ1).o: $(INC)$(OBJ7).h 
		$(CC) -o $@ -c $(SRC)$(OBJ1).c $(CFLAGS)


clean:
	rm -f $(BIN).o

mrproper: clean
	rm -f $(EXEC)