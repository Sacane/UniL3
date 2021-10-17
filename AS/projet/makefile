CC=gcc
CFLAGS=-Wall -ansi
LDFLAGS=-lfl 

PARSER=parser
LEXER=lexer
EXEC=tpcas

BIN=./bin/
SRC=./src/
OBJ=./obj/

$(BIN)$(EXEC): lex.yy.o $(PARSER).tab.c 
	$(CC) -o $@ $^ tree.c $(LDFLAGS)

$(SRC)$(PARSER).tab.c $(SRC)$(PARSER).tab.h: $(SRC)$(PARSER).y $(SRC)tree.h
	bison -d $(SRC)$(PARSER).y 

lex.yy.c: $(SRC)$(LEXER).lex $(SRC)$(PARSER).tab.h $(SRC)tree.h
	  flex $(LEXER).lex


$(OBJ)%.o: $(SRC)%.c $(SRC)%.h
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f lex.yy.*
	rm -f *.tab.*
	rm -f $(EXEC)