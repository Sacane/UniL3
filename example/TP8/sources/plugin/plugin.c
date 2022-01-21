#include "plugin.h"

BKEY_Plugin_List * BKEY_malloc_plugin_list(int nb_plugin) {
  BKEY_Plugin_List * plugins;
  plugins = (BKEY_Plugin_List *)malloc(sizeof(BKEY_Plugin_List));
  if (plugins == NULL) {
    fprintf(stderr, "[ Plugins list malloc failled contact administrateur system ]\n");
    exit(EXIT_FAILURE);
  }
  plugins->list = (BKEY_Plugin **)malloc(sizeof(BKEY_Plugin *) * nb_plugin);
  if (plugins->list == NULL) {
    fprintf(stderr, "[ Plugins malloc failled contact administrateur system ]\n");
    exit(EXIT_FAILURE);
  }
  plugins->nb_plugin = nb_plugin;
  printf("found %d potential plugins : \n", plugins->nb_plugin);
  return plugins;
}

BKEY_Plugin * BKEY_Plugin_load(void * lib_handel) {
  BKEY_Plugin * plugin;
  int (*arity)(void);
  char (*symbol)(void);
  char *error;

  plugin = (BKEY_Plugin *)malloc(sizeof(BKEY_Plugin));
  if (plugin == NULL) {
    return NULL;
  }
  /* Load mehtode eval in librairie */
  *(void **)(&plugin->eval) = dlsym(lib_handel, "eval");
  if ((error = dlerror()) != NULL) {
    fprintf(stderr, "%s\n", error);
    return NULL;
  }
  /* Load mehtode arity in librairie */
  *(void **)(&arity) = dlsym(lib_handel, "arity");
  if ((error = dlerror()) != NULL) {
    fprintf(stderr, "%s\n", error);
    return NULL;
  }
  /* Load mehtode symbol in librairie */
  *(void **)(&symbol) = dlsym(lib_handel, "symbol");
  if ((error = dlerror()) != NULL) {
    fprintf(stderr, "%s\n", error);
    return NULL;
  }

  /* Dont need the pointer of methode just the value */
  plugin->arity = arity();
  plugin->symbol = symbol();
  plugin->handel = lib_handel;
  return plugin;
}

BKEY_Plugin * BKEY_Plugin_get(BKEY_Plugin_List * plugins, char c) {
  int i;
  for (i = 0; i < plugins->nb_plugin; i++) {
    if ((plugins->list[i])->symbol == c) {
      return plugins->list[i];
    }
  }
  fprintf(stderr, "[ Any plugin loaded for this operation ]\n");
  return NULL;
}

void BKEY_free_plugin_list(BKEY_Plugin_List * plugins) {
  int i;
  for (i = 0; i < plugins->nb_plugin; i++) {
    if (plugins->list[i] != NULL) {
      if (plugins->list[i]->handel != NULL) {
        /* Close associeted lib_handel */
        dlclose(plugins->list[i]->handel);
      }
      free(plugins->list[i]);
    }
  }
  free(plugins);
}
