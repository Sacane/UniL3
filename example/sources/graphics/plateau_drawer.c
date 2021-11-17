  /*____________°\
 /.,------------,.\     EDITOR = ORHAN UYAR
///  .=^^^^^^^\__|\\    UNIVESITY = Gustave Eiffel
\\\   `------.   .//    LINK = www.brotherkey.fr
 `\\`--...._  `;//'     PS = HAVE FUN
   `\\.-,___;.//'
     `\\-..-//'
        \*/

#include "plateau_drawer.h"

/******************************************************************************/
void BKEY_window_gesture(int option) {
  if (option == 0) {
    MLV_free_window();
  } else if (option == 1) {
    MLV_create_window("BrotherKey Puzzle", "BGAME", PANEL_WIDTH, PANEL_HEIGHT);
  }
}
/******************************************************************************/
void BKEY_image_loader(Panel panel, char *link) {
  panel->image = MLV_load_image(link);
  if (panel->image == NULL) {
    /* Linked image failled to load */
    fprintf(stderr, "\n\t[ Immage %s cannot be loaded ]\n\n", link);
    exit(-1);
  }
  /* If image loaded succesfuly change proportion of image to adapt screen */
  MLV_resize_image_with_proportions(panel->image, PANEL_WIDTH, PANEL_HEIGHT);
}
/******************************************************************************/
void BKEY_draw_plateau(Panel panel) {
  int index;
  MLV_draw_filled_rectangle(0,0,PANEL_WIDTH,PANEL_HEIGHT, MLV_COLOR_AZURE);
  for (index = 0; index < panel->size*panel->size; index++) {
    if (panel->panel[index].x == panel->size-1 && panel->panel[index].y == panel->size-1) {
      BKEY_draw_empty_box(panel, index);
    } else {
      BKEY_draw_partial_image(panel, index);
    }
  }
  MLV_actualise_window();
}
/******************************************************************************/
void BKEY_draw_win_plateau(Panel panel) {
  int index;
  MLV_draw_filled_rectangle(0,0,PANEL_WIDTH,PANEL_HEIGHT, MLV_COLOR_AZURE);
  for (index = 0; index < panel->size*panel->size; index++) {
    BKEY_draw_partial_image(panel, index);
    MLV_actualise_window();
    MLV_wait_milliseconds(100);
  }
  MLV_draw_image(panel->image, 0, 0);
  MLV_actualise_window();
  MLV_wait_seconds(5);
}
/******************************************************************************/
void BKEY_draw_partial_image(Panel panel, int index) {
  int x_scale = PANEL_WIDTH / panel->size;/* Determinate x_scale about window */
  int y_scale = PANEL_HEIGHT/ panel->size;/* Determinate y_scale about window */
  MLV_draw_partial_image(
    panel->image,
    panel->panel[index].x * x_scale + 2,
    panel->panel[index].y * y_scale + 2,
    x_scale - 4,
    y_scale - 4,
    index % panel->size * x_scale + 2,
    index / panel->size * y_scale + 2
  );
}
/******************************************************************************/
void BKEY_draw_empty_box(Panel panel, int index) {
  int x_scale = PANEL_WIDTH / panel->size;/* Determinate x_scale about window */
  int y_scale = PANEL_HEIGHT/ panel->size;/* Determinate y_scale about window */
  MLV_draw_filled_rectangle(
    index % panel->size * x_scale + 2,
    index / panel->size * y_scale + 2,
    x_scale,
    y_scale,
    MLV_COLOR_AZURE
  );
}
