#include "../includes/parser.h"
#include <readline/readline.h>
#include <readline/history.h>


int main(int argc, char const *argv[])
{
    Stack st;
    int check_parsing;
    char *getline;
    Plugin_list *plugins;
    
    int quit = ON_PROCESS;
    st = st_initialize();

    plugins = plugin_loader();
    do{
        getline = readline("");
        add_history(getline);

        check_parsing = parse(&st, getline, &quit, plugins);
        free(getline);
    }while(quit != ON_EXIT || !check_parsing);
    
    st = st_clear(st);
    clear_history();
    rl_clear_history();
    free_plugin_list(plugins);
    printf("quit\n");
    return EXIT_SUCCESS;
}
