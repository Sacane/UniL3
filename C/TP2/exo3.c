#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* !!Using memory!! */
char *mirror_s(const char *string){
    char *res, tmp;
    
    int size = strlen(string), i, last;
    
    res = (char*)malloc(sizeof(char) * size);
    strcpy(res, string);

    for(i = 0; i < size / 2; i++){
        last = size - i - 1;
        tmp = res[i];
        res[i] = res[last];
        res[last] = tmp;
    }

    return res;
}

int main(int argc, char const *argv[])
{
    char *s_turned;
    if(argc < 2){
        fprintf(stderr, "You have to give one string as argument for this program\n");
        exit(1);
    }
    s_turned = mirror_s(argv[1]);
    printf("%s\n", s_turned);
    free(s_turned);
    return 0;
}
