CC=gcc
CMP=nasm
OPT=-nostartfiles -no-pie
TYPE=elf64

all: registers return_control loops tdc2_memory_access _anonymous my_putchar.o

lazy: lazy.o utils.o
	$(CC) -o $@ $< $(OPT)

registers: registers.o utils.o 
	$(CC) -o $@ $^ $(OPT)

return_control: return_control.o utils.o
	$(CC) -o $@ $^ $(OPT)

loops: loops.o utils.o my_putchar.o
	$(CC) -o $@ $^ $(OPT)

tdc2_memory_access: tdc2_memory_access.o utils.o 
	$(CC) -o $@ $^ $(OPT)

my_putchar: my_putchar.o utils.o
	$(CC) -o $@ $^ $(OPT)

_anonymous: _anonymous.o utils.o
	$(CC) -o $@ $^ $(OPT)

%.o: %.asm
	$(CMP) -f $(TYPE) -o $@ $<

clean:
	rm -f lazy lazy.o registers return_control loops _anonymous loops.o
	