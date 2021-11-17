
CC= gcc
CFLAGS=-Wall -ansi -g -O2
IMG= -fPIC
SHARED= -shared
LIBC=image_process

$(LIBC).so: $(LIBC).o
	$(CC) $(SHARED) $< -o $(LIBC).so $(CFLAGS)

$(LIBC).o:
	$(CC) -c $(LIBC).c $(IMG) $(CFLAGS) -o $(LIBC).o

