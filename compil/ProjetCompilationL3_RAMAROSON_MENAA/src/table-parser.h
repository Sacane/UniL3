#ifndef __TABLE_PARSER__H
#define __TABLE_PARSER__H


#include "symbols-table.h"


#include <unistd.h>
#include  <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define OPEN  0
#define CLOSE 1

int check_sem_err;
int check_warn;
int hasMain;

typedef struct list_table{
    
    Symbol_table *table;
    struct list_table *next;

}Table, *List;

List init_table_list();

int insertSymbolTableInList(List list, Symbol_table *table);
void print_chained_list(List lst);
List build_list_table(Node *root);
Symbol_table *getTableInListByName(char *name_table, List table_list);

void free_table();


#endif