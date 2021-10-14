#include "../includes/parser.h"

int is_numeric(char *input){
    long value;
    return (sscanf(input, "%ld", &value) == 1);
}

/**
 * @brief return the kind of the given character
 * @param input to identify
*/
static int input_kind(char input){
    int out;
    
    switch(input){
        case 'a':
        case 'c':
        case 'q':
        case 'p':
        case 'r':
            out = OPT;
            break;
        case '+':
        case '-':
        case '*':
        case '/':
        case '^':
        case '!':
        case '%':
            out = OPERATOR;
            break;
        default:
            out = ERROR;
            break;
    }
    return out;
}

int is_operator(char input){
    return (input_kind(input) == OPERATOR);
}

int is_opt(char input){
    return (input_kind(input) == OPT);
}

static char *substring_aux(char *src, int pos, int len) { 
 
    char * dest=NULL;             
    if (len>0) {
        dest = (char *)calloc(len+1, 1); 
        if(NULL != dest) {
            strncat(dest,src+pos,len);            
        }
    }                                       
    return dest;                            
}

char *subString(char *src, int pos) {
      return (pos > strlen(src)) ? src : substring_aux(src, pos, strlen(src));
}

static void tokenize(Stack *st, char *token, int *quit_opt){

   char *post_token;
   int value;
   if(token[0] == '\0'){
       return;
   }
   if(is_numeric(token)){
       value = strtol(token, &token, 10);
       (*st) = st_push((*st), value);
       if(!token){/*Token is null*/
            return;
       }
       else{
           tokenize(st, token, quit_opt);
       }
   }
   else{
       switch(input_kind(token[0])){
            case OPERATOR:
                eval(st, token[0]);
                break;
            case OPT:
                if(!opt_apply(st, token[0], quit_opt)){
                    fprintf(stderr, "E:Invalid token : %c", token[0]);
                    return;
                }
                break;
            case ERROR:
                fprintf(stderr, "E:Invalid token : %c\n", token[0]);
                break;
            default:
                fprintf(stderr, "invalid input\n");
        }
        post_token = subString(token, 1); 
        tokenize(st, post_token, quit_opt);
        free(post_token);
   }
}

/* Parse the input and apply the application */
int parse(Stack *st, char *input, int *quit_opt){

    char *tokens = strtok(input, " ");
    
    while(tokens != NULL){
        
        tokenize(st, tokens, quit_opt);

        tokens = strtok(NULL, " ");
    }
    return 1;
}


