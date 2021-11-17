  /*____________°\
 /.,------------,.\     EDITOR = ORHAN UYAR
///  .=^^^^^^^\__|\\    UNIVESITY = Gustave Eiffel
\\\   `------.   .//    LINK = www.brotherkey.fr
 `\\`--...._  `;//'     PS = HAVE FUN
   `\\.-,___;.//'
     `\\-..-//'
        \*/

#include "plateau.h"

Panel BKEY_init_GamePanel(int size) {
  int index;
  Panel panel = (Panel)malloc(sizeof(Panel));
  if (panel != NULL) { /* CHECK IF MALLOC SUCCED */
    panel->panel = (Box *)malloc(sizeof(Box)*(size*size));
    if (panel->panel != NULL) { /* CHECK IF MALLOC SUCCED */
      for (index = 0; index < (size*size); index++) {
        panel->panel[index].x = index % size;
        panel->panel[index].y = index / size;
      }
      panel->size = size;
      return panel; /* All malloc was succed so return inited Panel */
    }
  }
  /* If any malloc failled show a message and exit */
  fprintf(stderr, "\t [ Malloc failed please contact your admin ]\n");
  exit(-1);
}
/******************************************************************************/
Empty_Box BKEY_init_Empty_Box(int size) {
  Empty_Box box = (Empty_Box)malloc(sizeof(Empty_Box));
  if (box != NULL) { /* At start the Empty_Box was the last box */
    box->x = size-1;
    box->y = size-1;
    return box;
  }
  /* If malloc failled show a message and exit */
  fprintf(stderr, "\t [ Malloc failed please contact your admin ]\n");
  exit(-1);
}
/******************************************************************************/
void BKEY_free_Game(Panel panel, Empty_Box box) {
  BKEY_free_GamePanel(panel);
  free(box);
}
/******************************************************************************/
void BKEY_free_GamePanel(Panel panel) {
  MLV_free_image(panel->image);
  free(panel->panel);
  free(panel);
}
/******************************************************************************/
void BKEY_switch_box(Box *box1, Box *box2) {
  Box tmp = (*box1);
  (*box1) = (*box2);
  (*box2) = tmp;
}
