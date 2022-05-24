CC=gcc
CMP=nasm
OPT=-nostartfiles -no-pie
TYPE=elf64

all: exo4 

exo4: exo4.o utils.o
	$(CC) -o $@ $^ $(OPT)


%.o: %.asm
	$(CMP) -f $(TYPE) -o $@ $<

clean:
	rm -f exo4 exo4.o
	