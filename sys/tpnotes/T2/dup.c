#include <stdio.h>
#include <sys/signal.h>
#include <unistd.h>
#include "../try.h"
#include <fcntl.h>


//ref exercice 1 tp5

/*
Écrivez un programme qui redirige la sortie standard vers un fichier, puis effectue un ls vers ce
fichier. Il faut donc ouvrir ce fichier avec open(), puis utiliser dup2() afin que les accès ultérieurs à
la sortie standard se fassent sur le fichier. Ensuite, on peut faire un execlp() pour lancer ls -l, et
affichage se fera vers le fichier.

*/

int main(int argc, char const *argv[])
{
    

    int fd;

    fd = try(open("test.txt", O_WRONLY));

    //Objectif : Redirigé la sortie standard vers le fichier cible
    try(dup2(fd, STDOUT_FILENO));

    try(execlp("ls", "ls", "-l", (char *)NULL));


    return 0;
}
