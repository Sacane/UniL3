#include <MLV/MLV_all.h>

#include <stdlib.h>
#include <stdio.h>

#define IMAGE_SIZE 512
#define IMAGE_SIZE_X IMAGE_SIZE
#define IMAGE_SIZE_Y IMAGE_SIZE
#define PIXEL_SIZEOF 4


static int convert_levelC_to_levelPython(double levelPython){
    return levelPython * 255;
}

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


int max_pixel(unsigned char bitmap[PIXEL_SIZEOF]){
  int res, i;
  res = 0;
  for(i = 0; i < PIXEL_SIZEOF; i++){
    if(res < bitmap[i]){
      res = bitmap[i];
    }
  }
  return res;
}

int min_pixel(unsigned char bitmap[PIXEL_SIZEOF]){
  int res, i;
  res = bitmap[0];
  for(i = 1; i < PIXEL_SIZEOF; i++){
    if(res > bitmap[i]){
      res = bitmap[i];
    }
  }
  return res;
}

void grey_clarity_level(unsigned char bitmap[IMAGE_SIZE_Y][IMAGE_SIZE_X][PIXEL_SIZEOF]){
  int i,j;
  int value;
  for(i = 0; i < IMAGE_SIZE_X; i++){
    for(j = 0; j < IMAGE_SIZE_Y; j++){
      value = (max_pixel(bitmap[i][j]) + min_pixel(bitmap[i][j])) / 2;
      bitmap[i][j][0] = value;
      bitmap[i][j][1] = value;
      bitmap[i][j][2] = value;
    }
  } 
}

void grey_luminance_level(unsigned char bitmap[IMAGE_SIZE_Y][IMAGE_SIZE_X][PIXEL_SIZEOF]){
  int i,j;
  
  double value;
  for(i = 0; i < IMAGE_SIZE_X; i++){
    for(j = 0; j < IMAGE_SIZE_Y; j++){
      value = 0.2126*bitmap[i][j][0] + 0.7152 * bitmap[i][j][1] + 0.0722 * bitmap[i][j][2];
      bitmap[i][j][0] = value;
      bitmap[i][j][1] = value;
      bitmap[i][j][2] = value;
    }
  }
}

void black_white_thresholding(unsigned char bitmap[IMAGE_SIZE_Y][IMAGE_SIZE_X][PIXEL_SIZEOF]){
  int i, j;
  grey_luminance_level(bitmap);
  for(i = 0; i < IMAGE_SIZE_X; i++){
    for(j = 0; j < IMAGE_SIZE_Y; j++){
      if(bitmap[i][j][0] > (255/2)){
        bitmap[i][j][0] = 255;
        bitmap[i][j][1] = 255;
        bitmap[i][j][2] = 255;
      }
    }
  }
}

void to_red(unsigned char bitmap[IMAGE_SIZE_Y][IMAGE_SIZE_X][PIXEL_SIZEOF]){
  int i, j;
  for(i = 0; i < IMAGE_SIZE_X; i++){
    for(j = 0; j < IMAGE_SIZE_Y; j++){
      bitmap[i][j][0] = (255 + bitmap[i][j][0])/2;
    }
  }
}

void to_green(unsigned char bitmap[IMAGE_SIZE_Y][IMAGE_SIZE_X][PIXEL_SIZEOF]){
  int i, j;
  for(i = 0; i < IMAGE_SIZE_X; i++){
    for(j = 0; j < IMAGE_SIZE_Y; j++){
      bitmap[i][j][1] = (255*3 + bitmap[i][j][1])/4;
    }
  }
}

void average(unsigned char bitmap1[IMAGE_SIZE_Y][IMAGE_SIZE_X][PIXEL_SIZEOF], unsigned char bitmap2[IMAGE_SIZE_Y][IMAGE_SIZE_X][PIXEL_SIZEOF]){

  int i, j, k;

  for(i = 0; i < IMAGE_SIZE_X; i++){
    for(j = 0; j < IMAGE_SIZE_Y; j++){
      for(k = 0; k < 4; k++){
        bitmap1[i][j][k] = (bitmap1[i][j][k] + bitmap2[i][j][k])/ 2;
      }
    }
  }
}


void red_blue_degraded_img(unsigned char bitmap[IMAGE_SIZE_Y][IMAGE_SIZE_X][PIXEL_SIZEOF]){
  int i, j;
  float coef = 0;
  for (i=0 ; i<IMAGE_SIZE_Y ; ++i){
    for (j=0 ; j<IMAGE_SIZE_X ; ++j){
        coef = (i+j)/(1024.0);
        bitmap[i][j][0] = (1 - coef)*bitmap[i][j][0]; 
        bitmap[i][j][1] = 0;
        bitmap[i][j][2] = coef*bitmap[i][j][2];
    }
  }
}
