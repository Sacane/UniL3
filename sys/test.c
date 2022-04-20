#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include "try.h"



int main(int argc, char const *argv[])
{
    int fd;
    fd = open("_test_", O_CREAT | O_WRONLY);
    printf("fd : %d\n", fd);
    write(fd, "J'aime les pommes", 20);
    close(fd);
    return 0;
}
