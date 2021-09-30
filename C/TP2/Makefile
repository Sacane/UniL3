CC=gcc 
CFLAGS=-ansi -Wall -pg -lm -O3
OBJ1= exo1.o
OBJ2= exo2.o
OBJ3= exo3.o
OBJ4= blasay.o
OBJ5= bitcalc.o
OBJ6= bitstruct.o

all:
	make exo1
	make exo2
	make exo3
	make blasay
	make bitcalc
	make bitstruct

exo1: $(OBJ1)
		$(CC) -o $@ $^ $(CFLAGS)

exo2: $(OBJ2)
		$(CC) -o $@ $^ $(CFLAGS)

exo3: $(OBJ3)
		$(CC) -o $@ $^ $(CFLAGS)

blasay: $(OBJ4)
		$(CC) -o $@ $^ $(CFLAGS)

bitcalc: $(OBJ5)
		$(CC) -o $@ $^ $(CFLAGS)

bitstruct: $(OBJ6)
		$(CC) -o $@ $^ $(CFLAGS)

%.o: %.c
		$(CC) -c $< $(CFLAGS) 

clean:
		rm -f *.o 

mrproper: clean
		rm -f EXEC