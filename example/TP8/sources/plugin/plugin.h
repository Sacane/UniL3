  /*____________°\
 /.,------------,.\     EDITOR = ORHAN UYAR
///  .=^^^^^^^\__|\\    UNIVESITY = Gustave Eiffel
\\\   `------.   .//    LINK = www.brotherkey.fr
 `\\`--...._  `;//'     PS = HAVE FUN
   `\\.-,___;.//'
     `\\-..-//'
        \*/

/******************************************************************************
| TP 8 Prog - C
| Calculatos Plugin Gesture Lib
******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>

#ifndef __PLUGIN__
#define __PLUGIN__

typedef int (*eval)(int* args);

/*
 * Plugin definition
 * Give it by professor
 * Contain the handel of openned .so file
 * Must to be closed at the end of proc
 */
typedef struct {
  eval eval;
  int arity;
  char symbol;
  void * handel;
} BKEY_Plugin;

/*
 * Plugin list container
 */
typedef struct {
  BKEY_Plugin ** list;
  int nb_plugin;
} BKEY_Plugin_List;

/*
 * Malloc a plugin list container
 */
BKEY_Plugin_List * BKEY_malloc_plugin_list(int nb_plugin);

/*
 * Load the plugin and return malloced Plugin
 */
BKEY_Plugin * BKEY_Plugin_load(void * lib_handel);

/*
 * Get associeted plugin of char
 * If associeted plugin was founded return the pointer of the Plugin
 * If not found return NULL
 */
BKEY_Plugin * BKEY_Plugin_get(BKEY_Plugin_List * plugins, char c);

/*
 * Clear all plugin
 * And close the link about associeted handel link.
 */
void BKEY_free_plugin_list(BKEY_Plugin_List * plugins);

#endif
