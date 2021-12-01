CC=gcc
CFLAGS=-Wall -ansi

EXEC=larger_file

$(EXEC): file.o larger_file.o
	$(CC) -o $@ $^ $(CFLAGS)

file.o: file.h file.c
	$(CC) -c file.c $(CFLAGS)

larger_file.o: larger_file.c
	$(CC) -c larger_file.c $(CFLAGS)

clean: 
	rm -f entry.o
	rm -f tp5 out