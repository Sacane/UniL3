#include "../includes/parser.h"

int is_numeric(char *input){
    long value;
    return (sscanf(input, "%ld", &value) == 1);
}



static int input_kind(int input){
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

/*

- 1) take the token and test its value (numeric or not)
- 2)a) if its a numeric value : strtol and put the value in the stack and put the endPtr in the token
    2)a)I)  if the token is null return if not -> recurse
    2)b) if its not a numeric value : I) if token[0] != '\0' apply the option, then recursive-call
                                    II) else return

*/
static void parse_process(Stack *st, char *token, int *quit_opt){

   char *post_token;
   int value;
   if(is_numeric(token)){
       value = strtol(token, &token, 10);
       (*st) = st_push((*st), value);
       if(!token){/*Token is null*/
            return;
       }
       else{
           parse_process(st, token, quit_opt);
       }
   }
   else{
       if(token[0] == '\0'){
           return;
       }
       else{
            if(is_operator(token[0])){
                eval(st, token[0]);
            }
            if(is_opt(token[0])){
                opt_apply(st, token[0], quit_opt);
            }
            post_token = subString(token, 1); 
           parse_process(st, post_token, quit_opt);
           free(post_token);
       }
   }
}

/* Parse the input and apply the application */
int parse_input(Stack *st, char *input, int *quit_opt){

    char *tokens = strtok(input, " ");
    
    while(tokens != NULL){
        
        parse_process(st, tokens, quit_opt);

        tokens = strtok(NULL, " ");
    }
    return 1;
}


