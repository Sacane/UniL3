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

int get_total_score(JColor color, int number){
    int i, total, score_color;
    score_color = get_score_by_color(color);
    total = 0;
    for(i = 0; i < number; i++){
        total += score_color;
    }
    return total;
}


