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


void draw_score(int score){
    char *message = (char*)malloc(sizeof(char) * 10);
    sprintf(message, "Score : %d", score);
    const char *cons_message = message;
    MLV_draw_text(200, 200, message, MLV_COLOR_WHITE);
    free(message);
    
}

