#include "../includes/opt.h"
#include <readline/readline.h>
#include <readline/history.h>

int main(int argc, char const *argv[])
{
    Stack st;
    char *getline;
    st = st_initialize();
    
    /* TODO: loop + man stack
    do{

        getline = readline("");
        add_history(getline);
        st = st_push(st, 10);

    }while(getline[0] != 'q');
    clear_history();
    */
    long test = 0L;

    test = strtol("123+-", NULL, 10);
    printf("%ld\n", test);
    
    return 0;
}
