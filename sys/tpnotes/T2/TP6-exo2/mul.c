#include <stdio.h>
#include <unistd.h>


int main(int argc, char const *argv[])
{
    char buf[BUFSIZ];
    long a, b;
    setbuf(stdout, NULL);
    int n;
    while(fgets(buf, sizeof(buf), stdin)){
        if(sscanf(buf, "%ld%ld", &a, &b) == 2){
            printf("%ld\n", a * b);
        }
    }


    return 0;
}
