#include <stdio.h>
#include <unistd.h>


int main(int argc, char const *argv[])
{
    char buf[BUFSIZ];
    long a, b;
    setbuf(stdout, NULL);
    while(fgets(buf, sizeof(buf), stdin)){
        sscanf(buf, "%ld%ld", &a, &b);
        printf("%ld\n", a + b);
    }


    return 0;
}
