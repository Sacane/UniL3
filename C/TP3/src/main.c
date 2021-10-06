#include "../includes/opt.h"
#include <readline/readline.h>
#include <readline/history.h>

int main(int argc, char const *argv[])
{
    Stack st;
    char *getline;
    st = st_initialize();
    
    do{

        getline = readline("");
        add_history(getline);
        st = st_push(st, 10);

    }while(getline[0] != 'q');

    clear_history();

    return 0;
}
