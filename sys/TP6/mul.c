#include <stdio.h>
#include <stdlib.h>



int main(int argc, char const *argv[])
{
    int n, n2;
    char buf[BUFSIZ];

    while(fgets(buf, BUFSIZ, stdin)){

        

        sscanf(buf, "%d %d", &n, &n2);
        fprintf(stderr, "buf in mul : %s\n", buf);
        printf("%d\n", n * n2);
        fflush(stdout);
    }


    



    
    return 0;
}
