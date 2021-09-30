CC=gcc
CFLAGS=-ansi -Wall -pg
OBJ1= mytee.o 
OBJ2= exo2.o 
OBJ3= ppcm.o 

all:
	make mytee
	make exo2
	make ppcm


mytee: $(OBJ1)
		$(CC) -o $@ $^ $(CFLAGS)

exo2: $(OBJ2)
		$(CC) -o $@ $^ $(CFLAGS)

ppcm: $(OBJ3)
		$(CC) -o $@ $^ $(CFLAGS)


%.o: %.c
		$(CC) -c $< $(CFLAGS)

clean:
		rm -f *.o 

mrproper: clean
		rm -f EXEC