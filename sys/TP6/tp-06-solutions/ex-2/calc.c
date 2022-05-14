// To be compiled with the macro `OP` defined as either `+`, `-`, `*`, or `/`.
// In the makefile, this macro is defined via the compiler option `-D`.

#include <stdio.h>

int main(int argc, char **argv) {
  setbuf(stdout, NULL); // Unbuffered standard output to avoid deadlocks
  char buf[BUFSIZ];
  while (fgets(buf, sizeof(buf), stdin)) {
    long a, b;
    char junk; // For trailing garbage (https://stackoverflow.com/a/21888827)
    if (sscanf(buf, "%ld%ld %c", &a, &b, &junk) == 2) {
      printf("%ld\n", a OP b);
    }
    else {
      printf("%s: Syntax error\n", argv[0]);
    }
  }
}
