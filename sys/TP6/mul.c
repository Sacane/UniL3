#include <stdio.h>
#include <stdlib.h>



int main(int argc, char const *argv[])
{
    int n, n2;
    char buf[BUFSIZ];

    while(1){
        fgets(buf, BUFSIZ, stdin);
        sscanf(buf, "%d %d", &n, &n2);
        
        printf("%d\n", n * n2);
        fflush(stdout);
    }


    



    
    return 0;
}
