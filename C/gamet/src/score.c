#include "../includes/score.h"


static int my_pow(int a, int n){
    int i, res = a;
    for(i = 1; i < n; i++){
        res *= res;
    }
}

int get_score_by_color(JColor color){

    return my_pow(3, color);

}


