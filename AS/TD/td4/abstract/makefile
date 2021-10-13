# Makefile TP Flex

# $@ : the current target
# $^ : the current prerequisites
# $< : the first current prerequisite

CC=gcc
CFLAGS=-Wall
LDFLAGS=-Wall -lfl 
EXEC=translate
PARSER=parser
LEXER=lexer


$(EXEC): lex.yy.o $(PARSER).tab.c 
	$(CC) -o $@ $^ tree.c $(LDFLAGS)

$(PARSER).tab.c $(PARSER).tab.h: $(PARSER).y tree.h
	bison -d $(PARSER).y 

lex.yy.c: $(LEXER).lex $(PARSER).tab.h tree.h
	  flex $(LEXER).lex


%.o: %.c %.h
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f lex.yy.*
	rm -f *.tab.*
	rm -f $(EXEC)
