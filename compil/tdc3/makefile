CC=gcc
CMP=nasm
OPT=-nostartfiles -no-pie
TYPE=elf64

all: utils.o little_endian 

little_endian: little_endian.o utils.o
	$(CC) -o $@ $^ $(OPT)


%.o: %.asm
	$(CMP) -f $(TYPE) -o $@ $<

clean:
	rm -f *.o little_endian 
	