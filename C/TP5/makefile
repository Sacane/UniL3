CC=gcc
CFLAGS=-Wall 

EXEC=tp5

$(EXEC): entry.o code.o
	$(CC) -o $@ $^ $(CFLAGS)

entry.o: entry.c
	$(CC) -c entry.c $(CFLAGS)

clean: 
	rm -f entry.o
	rm -f tp5 out