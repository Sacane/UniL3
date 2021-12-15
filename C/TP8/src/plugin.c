#include "../includes/plugin.h"

/* Return 1 if the file has the extension .so else return 0 */
int plugin_file_filter(const struct dirent *dir){
    return(strstr(dir->d_name, ".so") != NULL);
}

Plugin_list *malloc_plugin_list(int nb_plugin){
    Plugin_list *list;
    if((list = (Plugin_list *)malloc(sizeof(Plugin_list))) == NULL){
        fprintf(stderr, "Error while allocate the plugin list's structure\n");
        exit(EXIT_FAILURE);
    }
    if((list->plugin_list = (Plugin**)malloc(sizeof(Plugin*) * nb_plugin)) == NULL){
        fprintf(stderr, "Error allocation of plugin list\n");
        exit(EXIT_FAILURE);
    }
    list->nb_plugin = nb_plugin;
    return list;
}

static void handle_dlError(char *error){
    if((error = dlerror()) != NULL){
        fprintf(stderr, "%s\n", error);
        exit(EXIT_FAILURE);
    }
}

Plugin *load_plugin(void *lib_handel){
    Plugin* plugin;
    int (*arity)(void);
    char (*symbol)(void);
    
    char *error = NULL;

    if((plugin = (Plugin*)malloc(sizeof(Plugin))) == NULL){
        fprintf(stderr, "Error while allocate a plugin\n");
        exit(EXIT_FAILURE);
    }

    *(void**)(&plugin->eval) = dlsym(lib_handel, "eval");
    handle_dlError(error);
    *(void**)(&arity) = dlsym(lib_handel, "arity");
    handle_dlError(error);
    *(void**)(&symbol) = dlsym(lib_handel, "symbol");
    handle_dlError(error);
    *(void**)(&plugin->check) = dlsym(lib_handel, "check");
    handle_dlError(error);

    plugin->arity = arity();
    plugin->symbol = symbol();

    plugin->handel = lib_handel;
    return plugin;
}

static void show_check_pluginDlOpen(Plugin *plugin, const char *path){
    (plugin != NULL) ? fprintf(stderr, "- %s ... loading OK\n", path) : fprintf(stderr, "- %s ... loading failed\n", path);
}

void open_plugin(char *file_name, Plugin **plugin){
    char path[250] = "plugins/";
    void *lib_handel;


    strcat(path, file_name);
    if(!(lib_handel = dlopen(path, RTLD_LAZY))){
        fprintf(stderr, "%s\n", dlerror());
        exit(EXIT_FAILURE);
    } else{
        (*plugin) = load_plugin(lib_handel);
        show_check_pluginDlOpen(*plugin, file_name);
    }

}



Plugin_list * plugin_loader(void){
    Plugin_list * plugins; 
    struct dirent **dirents;    /* Dirent how was stocked all file information */
    int n;                      /* Store the return of scandir who was the number of file founded */

    
    if ((n = scandir("plugins", &dirents, plugin_file_filter, NULL)) == -1) {      
        fprintf(stderr, "[ Plugins directory access denied ]\n");
        exit(EXIT_FAILURE);
    }

    fprintf(stderr, "Found %d potential plugins :\n", n);
    
    plugins = malloc_plugin_list(n); /* Initialize the plugins list */

    while (n--) {
        /* For all founded files, try to load him and store in plugin the list */
        open_plugin(dirents[n]->d_name, &(plugins->plugin_list[n]));
        free(dirents[n]); /* Free the dirents malloc for file */
    }
    free(dirents);
    return plugins;
}

Plugin *get_plugin_by_char(Plugin_list *list, char c){
    int i;
    for(i = 0; i < list->nb_plugin; i++){
        if((list->plugin_list[i])->symbol == c){
            return list->plugin_list[i];
        }
    }
    fprintf(stderr, "Can't find plugin for the operation : %c\n", c);
    return NULL;
}

void free_plugin_list(Plugin_list * plugins) {
    int i;
    for (i = 0; i < plugins->nb_plugin; i++) {
        if (plugins->plugin_list[i] != NULL) {
            if (plugins->plugin_list[i]->handel != NULL) {
            /* Close associeted lib_handel */
            dlclose(plugins->plugin_list[i]->handel);
            }
            free(plugins->plugin_list[i]);
        }
    }
    free(plugins);
}
