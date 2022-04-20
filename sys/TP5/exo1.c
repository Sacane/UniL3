#include <stdio.h>
#include <unistd.h>
#include "../try.h"
#include <fcntl.h>



/**
 * @brief change the fd of the stdout into the file given as parameter
 * @warning We suppose argv[1] to be the file out
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char const *argv[])
{
    
    if(argc < 2){
        return 1;
    }
    int creat = try(open(argv[1], O_CREAT));
    int out = try(open(argv[1], O_RDWR, S_IRUSR | S_IWUSR));
    try(dup2(out, STDOUT_FILENO));
    try(close(out));

    try(execlp("ls", "ls", "-l", (char*)NULL));


    return 0;
}
