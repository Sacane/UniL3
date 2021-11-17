  /*____________°\
 /.,------------,.\     EDITOR = ORHAN UYAR
///  .=^^^^^^^\__|\\    UNIVESITY = Gustave Eiffel
\\\   `------.   .//    LINK = www.brotherkey.fr
 `\\`--...._  `;//'     PS = HAVE FUN
   `\\.-,___;.//'
     `\\-..-//'
        \*/

#ifndef __PLATEAU__
#define __PLATEAU__

#define PLAT_WIDTH   4
#define PLAT_HEIGHT  4

#include <MLV/MLV_all.h>
#include <stdio.h>
#include <stdlib.h>

/*
* Box struct it's a box with a position
* Box represent a element how saved the original position
* Empty_Box represent the Empty_Box tracker take a current position of Empty_Box
*/
typedef struct box {
  int x;
  int y;
} Box, *Empty_Box;

/*
* GamePanel represent the playabel panel
* Take List of Box how represent a panel
* Size value take the dimension of gamePanel
* Image is the image which is played
*/
typedef struct gamePanel {
  Box *panel;
  int size;
  MLV_Image *image;
} GamePanel, *Panel;

/*
* Return Malloced Panel
* Take a size and malloc "size" elements Box
* Init the List of Box with the original position
* < WARNING > if any malloc failled exit
*/
Panel BKEY_init_GamePanel(int size);

/*
* Return Malloced Empty_Box
* Take a size to determiante the last elements
* At start the Empty_Box was the last
* < WARNING > if malloc failled exit
*/
Empty_Box BKEY_init_Empty_Box(int size);

/*
* Take two Box and switch the value inside the Box
*/
void BKEY_switch_box(Box *box1, Box *box2);

/*
* Free all element malloced to play
* Take malloced Panel and malloced Empty_Box
*/
void BKEY_free_Game(Panel panel, Empty_Box box);

/*
* Free all element malloc in Panel
* How contain Image, and List of Box
*/
void BKEY_free_GamePanel(Panel panel);


#endif
