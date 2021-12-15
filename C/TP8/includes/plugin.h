#ifndef __PLUGIN
#define __PLUGIN

#define _GNU_SOURCE

#include <dirent.h>
#include <dlfcn.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef long (*eval)(long* args);
typedef int (*check)(long* args);

typedef struct {

    eval eval;
    int arity;
    char symbol;
    check check;
    void * handel;
    
}Plugin;


typedef struct {

    Plugin **plugin_list;
    int nb_plugin;

}Plugin_list;


int is_plugin_file(const struct dirent *dir);

Plugin_list *malloc_plugin_list(int nb_plugin);
Plugin_list * plugin_loader(void);

Plugin *get_plugin_by_char(Plugin_list *list, char c);


void free_plugin_list(Plugin_list *list);

#endif