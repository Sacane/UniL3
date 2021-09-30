#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char c1;
    int i1;
    char c2;
    int i2;
}Test1;

typedef struct{
    char c1;
    char c2;
    int i1;
    int i2;
}Test2;

int main(int argc, char const *argv[])
{
    Test1 t1;
    Test2 t2;

    printf("size of the first structure : %ld\n", sizeof(t1));
    printf("size of the second structure : %ld\n", sizeof(t2));

    return 0;
}
/* We can see that the options -O{1, 2, 3} doesn't optimize anything
the size of t1 = 16 bytes and t2 = 12 bytes
*/