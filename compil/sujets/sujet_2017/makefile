CC=gcc
CMP=nasm
OPT=-nostartfiles -no-pie
TYPE=elf64

all: exo1


exo1: exo1.o utils.o 
	$(CC) -o $@ $^ $(OPT)

%.o: %.asm
	$(CMP) -f $(TYPE) -o $@ $<

clean:
	rm -f exo1.o exo1
	