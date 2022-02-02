#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "../try.h"

#define N 10000

static int arg_mode;

static void safe_write(int fd, char *buf, size_t size){
    size_t nw;
    if((nw = write(1, buf, 1)) == -1 || nw == 0){
        printf("Error\n");
        exit(EXIT_FAILURE);
    }
}

void rewrite_by_fd(int fd, char *buf, int line_mode){
    int check = 1;
    size_t nw;
    int line_count = 1;
    char line_start[3];
    
    while (check != 0){
        
        check = read(fd, buf, 1);
        if(line_mode){
            sprintf(line_start, "%d ", line_count); 
            safe_write(1, line_start, 4);
        }
        
        if(line_mode && buf[0] == '\n'){
            line_count++;
        }
        safe_write(1, buf, 2);

    }
}

int main(int argc, char *const *argv)
{
    const char * optstring = "n";
    int check = 1;
    char buffer[N];
    int fd, i;
    int count;
    int file_read = 0;
    int val;
    int print_line = 0;

    while(EOF != (val = getopt(argc, argv, optstring))){
        switch(val){
            case 'n':
                printf("this program should print the lines\n");
                print_line = 1;
                break;
            default:
                break;
        }
    }

    if(argc == 1 || argv[1][0] == '-'){
        printf("%d\n", optind);
        rewrite_by_fd(STDIN_FILENO, buffer, print_line);
    }
    else{
        arg_mode = 1;
        for(i = 0; i < argc - 1; i++){
            
            fd = try(open(argv[i+1], O_RDONLY));
            rewrite_by_fd(fd, buffer, print_line);
            close(fd);
        }
        
    }



    return 0;
}
