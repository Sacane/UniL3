#include "pluginsLoader.h"

BKEY_Plugin_List * BKEY_plugin_loader(void){
  BKEY_Plugin_List * plugins; /* Custom Plugins list */
  struct dirent **dirents;    /* Dirent how was stocked all file inforamtion */
  int n;                      /* Stock the return of scandir who was the number of file fouded */

  n = scandir("plugins", &dirents, BKEY_file_filter, NULL);
  if (n == -1) {              /* Failled to access on folder */
    fprintf(stderr, "[ Plugins directory access failled ]\n");
    exit(EXIT_FAILURE);
  }

  plugins = BKEY_malloc_plugin_list(n); /* Initialize the plugins list */

  while (n--) {
    /* For all file founder try to load him and stock in plugin list */
    BKEY_Plugin_dlopen(dirents[n]->d_name, &(plugins->list[n]));
    free(dirents[n]); /* Free the dirents malloc for file */
  }
  free(dirents);
  return plugins;
}

int BKEY_file_filter(const struct dirent * dir) {
  if (strstr(dir->d_name, ".so")) /* Check if .so extension prensent in file_name */
    return 1;
  return 0;
}

void BKEY_Plugin_dlopen(char * file_name, BKEY_Plugin ** plugin) {
  char path[255] = "plugins/";
  void * lib_handel;

  strcat(path, file_name);
  lib_handel = dlopen(path, RTLD_LAZY);
  
  if (lib_handel == NULL) { /* Check if the file was malformed */
    fprintf(stderr, " - %s.. cannot loading MALFORMED\n", path);
    (*plugin) = NULL;
  } else {
    (*plugin) = BKEY_Plugin_load(lib_handel); /* Try to load plugin */
    if ((*plugin) == NULL) {
      printf(" - %s.. loading FAILED\n",path);
    } else {
      printf(" - %s.. loading OK\n", path);
    }
  }

}
