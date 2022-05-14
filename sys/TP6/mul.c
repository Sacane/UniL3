#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>




int main(int argc, char **argv) {
  setbuf(stdout, NULL); // Unbuffered standard output to avoid deadlocks
  char buf[BUFSIZ];
  while (fgets(buf, sizeof(buf), stdin)) {
    long a, b;
    if (sscanf(buf, "%ld%ld", &a, &b) == 2) {
      printf("%ld\n", a * b);
    }
  }
}