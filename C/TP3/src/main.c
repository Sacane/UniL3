#include "../includes/opt.h"
#include <readline/readline.h>
#include <readline/history.h>

int main(int argc, char const *argv[])
{
    Stack st;
    char *getline;
    int res;
    st = st_initialize();


    do{
        getline = readline("");
        add_history(getline);

    }while(getline[0] != 'q');

    return 0;
}
