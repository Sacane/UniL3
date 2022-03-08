CC=gcc
CMP=nasm
OPT=-nostartfiles -no-pie
TYPE=elf64

all: utils.o start volatils

start: utils.o function.o start.o
	$(CC) -o $@ $^ $(OPT)

volatils: utils.o function.o volatils.o
	$(CC) -o $@ $^ $(OPT)


utils.o: ../utils.asm 
	$(CMP) -f $(TYPE) -o $@ $<
%.o: %.asm
	$(CMP) -f $(TYPE) -o $@ $<

clean:
	rm -f *.o start volatils function
	