CC=gcc
CFLAGS=-ansi -Wall -ldl
LFLAGS= -lreadline
EXEC= mycalc
OBJ1= main.o
OBJ2= operator.o
OBJ3= stack.o
OBJ4= opt.o
OBJ5= parser.o
OBJ6= eval.o




SRC=./src/
BIN=./bin/
INC=./includes/

PATH_PLUGINS_SRC=$(SRC)plugins/
PATH_PLUGINS_OUT=plugins/
PLUGINS=$(wildcard $(PATH_PLUGINS_SRC)*.c)

all: clean uninstall
	 make $(EXEC)
	 make install
	 

$(EXEC): $(BIN)$(OBJ1) $(BIN)$(OBJ2) $(BIN)$(OBJ3) $(BIN)$(OBJ4) $(BIN)$(OBJ5) $(BIN)$(OBJ6) $(BIN)plugin.o
		$(CC) -o $@ $^ $(CFLAGS) $(LFLAGS)

$(BIN)$(OBJ2): $(INC)operator.h 
		$(CC) -o $@ -c $(SRC)operator.c $(CFLAGS) -lm

$(BIN)$(OBJ3):$(INC)stack.h 
		$(CC) -o $@ -c $(SRC)stack.c $(CFLAGS)

$(BIN)$(OBJ4):$(INC)opt.h $(INC)operator.h $(INC)stack.h
		$(CC) -o $@ -c $(SRC)opt.c $(CFLAGS)

$(BIN)$(OBJ5):$(INC)parser.h $(INC)opt.h $(INC)eval.h
		$(CC) -o $@ -c $(SRC)parser.c $(CFLAGS)
		
$(BIN)$(OBJ6): $(INC)eval.h $(INC)stack.h $(INC)operator.h
		$(CC) -o $@ -c $(SRC)eval.c $(CFLAGS)

$(BIN)$(OBJ1): $(SRC)main.c $(INC)parser.h
		$(CC) -o $@ -c $(SRC)main.c $(CFLAGS)

$(BIN)plugin.o: $(SRC)plugin.c $(INC)plugin.h
		$(CC) -o $@ -c $(SRC)plugin.c $(CFLAGS)

$(PATH_PLUGINS_OUT)%.so: $(PATH_PLUGINS_SRC)%.c
		$(CC) -shared -o $@ -fPIC $<	


install: $(patsubst $(PATH_PLUGINS_SRC)%.c, $(PATH_PLUGINS_OUT)%.so, $(PLUGINS))

uninstall:
	rm -f $(PATH_PLUGINS_OUT)*.so

clean:
		rm -f $(BIN)*.o 

mrproper: clean uninstall
		rm -f $(EXEC)