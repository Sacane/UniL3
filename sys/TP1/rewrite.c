#include <stdio.h>

void rewrite(){ // time : 0.5 minutes
    int c;
    
    do {
        c = fgetc(stdin);

        fputc(c, stdout);

    }while(c != EOF);
}

void rewrite_without_bufferisation(){ //time : 3.38 minutes
    int c;
    char buf[BUFSIZ];
    do{
        setbuf(stdin, NULL);
        c = fgetc(stdin);

        setbuf(stdout, buf);
        fputc(c, stdout);
    }while(c != EOF);
}

int main(int argc, char const *argv[])
{

    rewrite();
    return 0;
}