#include "../includes/parser.h"
#include <readline/readline.h>
#include <readline/history.h>


int main(int argc, char const *argv[])
{
    Stack st;
    int check_parsing;
    char *getline;
    
    
    int quit = ON_PROCESS;
    st = st_initialize();

    do{
        getline = readline("");
        add_history(getline);

        check_parsing = parse(&st, getline, &quit);
        free(getline);
    }while(quit != ON_EXIT || !check_parsing);
    
    st = st_clear(st);
    clear_history();
    rl_clear_history();

    printf("quit\n");
    return EXIT_SUCCESS;
}
