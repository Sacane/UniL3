#include <MLV/MLV_all.h>

#include <stdlib.h>
#include <stdio.h>

#define IMAGE_SIZE 512
#define IMAGE_SIZE_X IMAGE_SIZE
#define IMAGE_SIZE_Y IMAGE_SIZE
#define PIXEL_SIZEOF 4


/* 600 fois plus rapide que sa version en python... */
void invert_color(unsigned char bitmap[IMAGE_SIZE_Y][IMAGE_SIZE_X][PIXEL_SIZEOF]){
  int i, j;

    for (i=0 ; i<IMAGE_SIZE_Y ; ++i){
        for (j=0 ; j<IMAGE_SIZE_X ; ++j){
            bitmap[i][j][0] = 255 - bitmap[i][j][0]; /* red */
            bitmap[i][j][1] = 255 - bitmap[i][j][1]; /* green */
            bitmap[i][j][2] = 255 - bitmap[i][j][2]; /* blue */
        }
    }
}

void average_grey_level(unsigned char bitmap[IMAGE_SIZE_Y][IMAGE_SIZE_X][PIXEL_SIZEOF]){
  int i,j;
  int value;
  for(i = 0; i < IMAGE_SIZE_X; i++){
    for(j = 0; j < IMAGE_SIZE_Y; j++){
      value = (bitmap[i][j][0] + bitmap[i][j][0] + bitmap[i][j][0]) / 3;
      bitmap[i][j][0] = value;
      bitmap[i][j][1] = value;
      bitmap[i][j][2] = value;
    }
  }
}


