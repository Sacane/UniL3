CC=gcc

DEPS= lex.yy

OBJ=$(DEPS:%=obj/%.o)

CFLAGS=-Wall -ly -lfl -pedantic -g 

EXEC=tpcas

PARSER=exp-tpc

LEXER=lexer

all : makedirs bin/$(EXEC)

makedirs:

	@mkdir -p bin

	@mkdir -p obj

bin/$(EXEC): obj/lex.yy.o  ./$(PARSER).tab.c 

	$(CC) -o $@ $^ ./tree.c $(LDFLAGS)

./lex.yy.c: ./$(LEXER).lex ./tree.h ./$(PARSER).tab.h

	flex -o $@ ./$(LEXER).lex

./$(PARSER).tab.c ./$(PARSER).tab.h: ./$(PARSER).y

	bison -d -r all ./$(PARSER).y


obj/lex.yy.o: ./lex.yy.c

	$(CC) -c ./lex.yy.c -o obj/lex.yy.o $(CFLAGS)

obj/tree.o: ./tree.c ./tree.h

	$(CC) -c ./tree.c -o obj/tree.o $(CFLAGS)

clean:

	rm -f ./lex.yy.* ./$(PARSER).tab.* obj/* bin/* *.output