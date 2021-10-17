#include "../includes/score.h"



int get_score_by_color(JColor color){

    return pow(3, color);

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


