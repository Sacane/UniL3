/**
 * @author Marc AGNETTI
 * @create date 2021-11-12 17:37:11
 * @modify date 2021-11-18 17:47:42
 * @desc Source file for the project's Main
 */


#include "../inc/binKey.h"


int main(int argc, char *argv[]){
    Bitkey B;
    generate_generation_key(&B, 7);
    fprintf(stderr, "fitness : %f\n", fitness_key(&B));
    enter_the_matrix(&B);
    return 0;
}
