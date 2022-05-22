CC=gcc
CMP=nasm
OPT=-nostartfiles -no-pie
TYPE=elf64

all: exo1 exo2


exo1: exo1.o 
	$(CC) -o $@ $^ $(OPT)
exo2: exo2.o
	$(CC) -o $@ $^ $(OPT)

%.o: %.asm
	$(CMP) -f $(TYPE) -o $@ $<

clean:
	rm -f exo1.o exo1
	