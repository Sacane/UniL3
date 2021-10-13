#include "../includes/parser.h"
#include <readline/readline.h>
#include <readline/history.h>


int main(int argc, char const *argv[])
{
    Stack st;
    char *getline;
    st = st_initialize();
    
    int quit = ON_PROCESS;

    do{
        getline = readline("");
        add_history(getline);

        parse_input(&st, getline, &quit);
        free(getline);
    }while(quit != ON_EXIT);
    
    st = st_clear(st);
    clear_history();
    rl_clear_history();

    printf("quit\n");
    return 0;
}
