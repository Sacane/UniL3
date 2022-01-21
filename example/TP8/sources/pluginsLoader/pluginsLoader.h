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
| Calculatos Plugin Loader
******************************************************************************/

#define _GNU_SOURCE

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

#include "../plugin/plugin.h"

#ifndef __PLUGINSLOADER__
#define __PLUGINSLOADER__


/*
 * Plugin Loader
 * Get all .so file in plugins folder
 * Launch BKEY_Plugin_dlopen for all file founded in folder
 * Return list of plugins succedfuly loaded.
 */
BKEY_Plugin_List * BKEY_plugin_loader(void);

/*
 * Plugin file filter methode.
 * Return 1 is the name of file contain .so
 * Return 0 if not present
 */
int BKEY_file_filter(const struct dirent * dir);

/*
 * Get a file name and load if it's possible the module in plugin.
 */
void BKEY_Plugin_dlopen(char * file_name, BKEY_Plugin ** plugin);

#endif
