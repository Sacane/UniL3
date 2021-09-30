# Makefile TP Flex

# $@ : the current target
# $^ : the current prerequisites
# $< : the first current prerequisite

CC=gcc
CFLAGS=-Wall
LDFLAGS=-Wall -lfl
EXEC=ex2

# all: $(EXEC) clean

$(EXEC): lex.yy.o $(EXEC).tab.c 
	$(CC) -o $@ $^ $(LDFLAGS)

$(EXEC).tab.c: $(EXEC).y
	bison $(EXEC).y

lex.yy.c: $(EXEC).lex
	  flex $(EXEC).lex

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f lex.yy.*
