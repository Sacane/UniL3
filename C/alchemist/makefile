CC=gcc
CFLAGS=-ansi -Wall 
LDFLAGS=-lMLV
EXEC=alchemist

OBJ1=main
OBJ2=container
OBJ3=ball
OBJ4=game_logic
OBJ5=score
OBJ6=board
OBJ7=test
OBJ8=vue
OBJ9=controller
OBJ10=game_process

SRC=./src/
BIN=./bin/
INC=./includes/

all: mrproper $(EXEC)
	 

$(EXEC): $(BIN)$(OBJ1).o $(BIN)$(OBJ3).o $(BIN)$(OBJ4).o $(BIN)$(OBJ5).o $(BIN)$(OBJ6).o $(BIN)$(OBJ7).o $(BIN)$(OBJ2).o $(BIN)$(OBJ8).o $(BIN)$(OBJ9).o $(BIN)$(OBJ10).o
		$(CC) -o $@ $^ $(CFLAGS) -lm $(LDFLAGS)

$(BIN)$(OBJ2).o: $(INC)$(OBJ2).h $(INC)$(OBJ3).h
		$(CC) -o $@ -c $(SRC)$(OBJ2).c $(CFLAGS)

$(BIN)$(OBJ3).o: $(INC)$(OBJ3).h
		$(CC) -o $@ -c $(SRC)$(OBJ3).c $(CFLAGS)

$(BIN)$(OBJ4).o: $(INC)$(OBJ4).h $(INC)$(OBJ6).h $(INC)$(OBJ2).h
		$(CC) -o $@ -c $(SRC)$(OBJ4).c $(CFLAGS)

$(BIN)$(OBJ5).o: $(INC)$(OBJ5).h $(INC)$(OBJ3).h
		$(CC) -o $@ -c $(SRC)$(OBJ5).c $(CFLAGS) 

$(BIN)$(OBJ6).o: $(INC)$(OBJ6).h $(INC)$(OBJ3).h
		$(CC) -o $@ -c $(SRC)$(OBJ6).c $(CFLAGS)

$(BIN)$(OBJ7).o: $(INC)$(OBJ7).h $(INC)$(OBJ2).h $(INC)$(OBJ8).h $(INC)$(OBJ9).h $(INC)$(OBJ10).h
		$(CC) -o $@ -c $(SRC)$(OBJ7).c $(CFLAGS) $(LDFLAGS)

$(BIN)$(OBJ1).o: $(INC)$(OBJ6).h 
		$(CC) -o $@ -c $(SRC)$(OBJ1).c $(CFLAGS) $(LDFLAGS)

$(BIN)$(OBJ8).o: $(INC)$(OBJ8).h $(INC)$(OBJ6).h $(INC)$(OBJ2).h
		$(CC) -o $@ -c $(SRC)$(OBJ8).c $(CFLAGS) $(LDFLAGS)

$(BIN)$(OBJ9).o: $(INC)$(OBJ9).h $(INC)$(OBJ6).h $(INC)$(OBJ10).h
		$(CC) -o $@ -c $(SRC)$(OBJ9).c $(CFLAGS) $(LDFLAGS)

$(BIN)$(OBJ10).o:$(INC)$(OBJ10).h $(INC)$(OBJ8).h $(INC)$(OBJ4).h
		$(CC) -o $@ -c $(SRC)$(OBJ10).c $(CFLAGS) $(LDFLAGS)

clean:
	rm -f $(BIN)*.o

mrproper: clean
	rm -f $(EXEC)