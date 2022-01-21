#include "pile.h"

Pile * malloc_PILE(int value) {
  Pile * pile = (Pile *)malloc(sizeof(Pile));
  (*pile).previous = NULL;
  (*pile).value = value;
  return pile;
}

Pile * add_PILE(Pile * pile, int value) {
  Pile * p = malloc_PILE(value);
  if (p == NULL) {
    free_PILE(pile);
    fprintf(stderr, "Adding in Pile failled, all pile cleared...");
    exit(-1);
  } else {
    if (pile == NULL) {
      return p;
    } else {
      (*p).previous = pile;
      return p;
    }
  }
}

void free_PILE(Pile * pile) {
  if (pile != NULL) {
    free_PILE((*pile).previous);
    (*pile).previous = NULL;
    free(pile);
    pile = NULL;
  }
}


void print_PILE(Pile * pile) {
  if (pile != NULL) {
    printf("%d\n", (*pile).value);
    print_PILE((*pile).previous);
  }
}

int alter_PILE_from_plugin(Pile ** pile,BKEY_Plugin_List * plugins, char c){
  BKEY_Plugin * plugin;
  plugin = BKEY_Plugin_get(plugins, c);
  if (plugin != NULL) {
    switch (plugin->arity) {
      case 1:
        if ((*pile) != NULL) {
          (*pile)->value = plugin->eval(&((*pile)->value));
          return 1;
        } else {
          fprintf(stderr, "\t[ Empty pile ]\n");
          return 0;
        }
        break;
      case 2:
        if (previous_PILE_EXIST((*pile)) == 1) {
          int valeur[2];
          valeur[0] = ((*pile)->previous->value);
          valeur[1] = ((*pile)->value);
          (*pile)->previous->value = plugin->eval(valeur);
          (*pile) = pop_PILE((*pile));
          return 1;
        } else {
          return 0;
        }
        break;
      default:
        fprintf(stderr, "\t[ Cannot support over 2 args ]\n");
        return 0;
        break;
    }
  } else {
    return 0;
  }
}

int previous_PILE_EXIST(Pile * pile) {
  if (pile == NULL) {
    fprintf(stderr, "\t[ Empty pile ]\n");
    return 0;
  } else {
    if ((*pile).previous == NULL) {
      fprintf(stderr, "\t[ Empty previous pile ]\n");
      return 0;
    }
  }
  return 1;
}


Pile * pop_PILE(Pile * pile) {
  if (pile == NULL) {
    fprintf(stderr, "\t[ Nothing to POP ]\n");
    return NULL;
  } else if ((*pile).previous == NULL ) {
    free(pile);
    return NULL;
  } else {
    Pile * p = (*pile).previous;
    free(pile);
    return p;
  }
}
