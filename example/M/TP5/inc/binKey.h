/**
 * @author Marc AGNETTI
 * @create date 2021-11-12 17:38:08
 * @modify date 2021-11-18 17:47:42
 * @desc Header file for the binary key
 */


#ifndef __BINKEY__
#define __BINKEY__


    /* Modules */


    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <time.h>
    #include "code.h"


    /* Macros */


    #define NB_OCT 32


    /* Fonctions */


    int generate_random_key();


    int sort_bitkey(Bitkey* B);


    int merge_keys(Bitkey a, Bitkey b, Bitkey c, Bitkey* res);


    int generate_generation_key(Bitkey* B, int d);


#endif
