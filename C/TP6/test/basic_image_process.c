/* Basic image process */

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
