#include "../includes/parser.h"


int is_numeric(char *input){
    return (strtol(input, NULL, 10) == 0L);
}

int input_kind(char input){
    switch(input){
        case 'a':
        case 'c':
        case 'q':
        case 'p':
        case 'r':
            return OPT;
        case '+':
        case '-':
        case '*':
        case '/':
        case '^':
        case '!':
            return OPERATOR;
        default:
            printf("incorrect input\n");
            return ERROR;
            break;
    }

    
}

int parse_input(Stack *st, char *input){
    int size, i, check;

    size = strlen(input);
    check = is_numeric(input);
    
    if(check != 0L){ /*The input is a number*/
        (*st) = st_push(*st, check);
        return 1;
    }
    if(input_kind(input[0]) == OPT && opt_apply(*st, input[0])){ /*The input is an option*/
        return 1;
    }
    
    /*input is Operator*/
    for(i = 0; i < size; i++){
        if(input_kind(input[i]) == OPERATOR && !eval(*st, input[i])){
            continue;
        }
    }
    return 1;
    
    
}


