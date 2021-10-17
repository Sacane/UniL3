# Makefile TP Flex

CC=gcc
CFLAGS=-Wall
LDFLAGS=-Wall -lfl 
EXEC=ex2


$(EXEC): lex.yy.o $(EXEC).tab.c 
	$(CC) -o $@ $^ $(LDFLAGS)

$(EXEC).tab.c $(EXEC).tab.h: $(EXEC).y
	bison -d $(EXEC).y

lex.yy.c: $(EXEC).lex $(EXEC).tab.h
	  flex $(EXEC).lex

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f lex.yy.*
	rm -f $(EXEC).tab.*
	rm -f $(EXEC)
