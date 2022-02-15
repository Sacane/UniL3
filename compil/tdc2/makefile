CC=gcc
CMP=nasm
OPT=-nostartfiles -no-pie
TYPE=elf64

all: lazy registers return_control loops tdc2_memory_access

lazy: lazy.o utils.o
	$(CC) -o $@ $< $(OPT)

registers: registers.o utils.o 
	$(CC) -o $@ $^ $(OPT)

return_control: return_control.o utils.o
	$(CC) -o $@ $^ $(OPT)

loops: loops.o utils.o 
	$(CC) -o $@ $^ $(OPT)

tdc2_memory_access: tdc2_memory_access.o utils.o 
	$(CC) -o $@ $^ $(OPT)

%.o: %.asm
	$(CMP) -f $(TYPE) -o $@ $<

clean:
	rm -f lazy *.o registers return_control loops
	