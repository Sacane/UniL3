#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "code.h"

int random_generate_octet(){
    static int first = 0;
    if(first % 2 == 0){
        srand(time(NULL));
        first++;
    }
    return rand() % 256;
}

Bitkey random_generate_key() {
    Bitkey key;

    for (int i = 0; i < NB_OCT; i++) {
        
        key.values[i] = random_generate_octet();
    }
    return key;
}

int compare( const void* a, const void* b) {
    Bitkey key1 = *((Bitkey*)a);
    Bitkey key2 = *((Bitkey*)b);
    
    if ( fitness_key(&key1) > fitness_key(&key2) ) 
        return -1;
    else   
        return 1;
}

Bitkey coupling(Bitkey cle1, Bitkey cle2, Bitkey cle3) {
    int i;
    Bitkey child;
    for (i = 0; i < NB_OCT; i++) {
        child.values[i] = (cle1.values[i] & cle2.values[i]) | (cle1.values[i] & cle3.values[i]) | (cle2.values[i] & cle3.values[i]);
    }
    return child;
}


void generate_cle_generation(Bitkey* B, int d) {
    Bitkey tab[8];
    if (d < 0){
        printf("Error argument d non-valide");
        return;
    }
    if (d == 0) {
        *B = random_generate_key();
        return;
    }
    
    /* generation of 8 keys d-1 */
    for (int i = 0; i < 8; i++) 
        generate_cle_generation(&tab[i], d - 1);
        
    /* sort of the array */
    qsort(tab, 8, sizeof(Bitkey), compare);

    /* coupling 3 of the best keys */
    (*B) = coupling(tab[0], tab[1], tab[2]);
    
}

int main(int argc, char* argv[]) {
    Bitkey key;
    printf("Hi\n");
    int generation;
    generation = 7;
    float fitness_value = 0.0;
    while (fitness_value < 100.000) {       /* Bitkey have a best value */
        generate_cle_generation(&key, 7);    /* Call generation with 4 recursive*/
        fitness_value = fitness_key(&key);
        printf("fitness : %f\n", fitness_key(&key));
    }

    enter_the_matrix(&key);
    generation++;

    return 0;
}