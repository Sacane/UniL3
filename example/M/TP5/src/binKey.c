/**
 * @author Marc AGNETTI
 * @create date 2021-11-12 17:38:08
 * @modify date 2021-11-18 17:47:42
 * @desc Source file for the binary key
 */


#include "../inc/binKey.h"


int generate_random_key(Bitkey* B){
    int i;
    
    if (B == NULL){
        return 1;
    }
    
    srand(time(NULL));
    for (i = 0 ; i < NB_OCT ; i++){
        B->values[i] = rand() % 256;
    }
    
    return 0;
}

int compare( const void* a, const void* b) {
    Bitkey key1 = *((Bitkey*)a);
    Bitkey key2 = *((Bitkey*)b);
    
    if ( fitness_key(&key1) > fitness_key(&key2) ) 
        return -1;
    else   
        return 1;
}

int sort_bitkey(Bitkey* tab){
    int i, j;
    Bitkey key;
    for (i = 0 ; i < 8 - 1 ; i++){
        for (j = i + 1 ; j < 8 ; j++){
            if (fitness_key(&tab[i]) > fitness_key(&tab[j])){
                key = tab[i];
                tab[i] = tab[j];
                tab[j] = key;
            }
        }
    }
    return 0;
}

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
    int i;
    for ( i = 0; i < NB_OCT; i++) {
        
        key.values[i] = random_generate_octet();
    }
    return key;
}

int merge_keys(Bitkey a, Bitkey b, Bitkey c, Bitkey* res){
    int i;
    
    for (i = 0 ; i < NB_OCT ; i++){
        res->values[i] = (a.values[i] & b.values[i]) 
                            | (a.values[i] & c.values[i]) 
                            | (b.values[i] & c.values[i]);
    }

    return 0;
}
Bitkey coupling(Bitkey key1, Bitkey key2, Bitkey key3) {
    int i;
    Bitkey child;
    for (i = 0; i < NB_OCT; i++) {
        child.values[i] = (key1.values[i] & key2.values[i]) | 
                          (key1.values[i] & key3.values[i]) | 
                          (key2.values[i] & key3.values[i]);
    }
    return child;
}


int generate_generation_key(Bitkey* B, int d){
    Bitkey tab[8];
    int i, r;
    
    if (d == 0){
        (*B) = random_generate_key();
        return 0;
    }
    
    for (i = 0 ; i < 8 ; i++){
        r = generate_generation_key(&tab[i], d - 1);
    }
    
    sort_bitkey(B);

    *B = coupling(tab[0], tab[1], tab[2]);

    return 0;
}
