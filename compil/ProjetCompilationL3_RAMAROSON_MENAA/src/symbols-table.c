#include "symbols-table.h"


unsigned long hash(unsigned char *str)
{
    unsigned long hash = 0;
    int c;

    while (c = *str++)
        hash = hash + c; 

    return hash;
}

Symbol_table *newSymbolTable(char *name_table){
    Symbol_table *table;
    int i;
    if(!(table = malloc(sizeof(Symbol_table)))){
        raiseError(-1, "Failed to allocate the table\n");
        return NULL;
    }
    if(!(table->name_table = malloc(sizeof(char) * strlen(name_table)))){
        raiseError(-1, "Failed to allocate the table's name\n");
        return NULL;
    }
    if(!(table->s = malloc(sizeof(Symbol) * INIT_TABLE_SIZ))){
        DEBUG("Failed to allocated the symbol table : %s\n", name_table);
        return NULL;
    }
    strcpy(table->name_table, name_table);
    table->nb_symbol = 0;
    table->total_size = 0;
    table->size = INIT_TABLE_SIZ;
    table->nb_parameter = 0;

    for(i = 0; i < INIT_TABLE_SIZ; i++){
        table->s[i] = calloc_symbol();
    }
    return table;
}


int is_identifier_key_in_table(Symbol_table *table, unsigned long symbol_key){
    return (table->s[symbol_key].symbol_name != NULL);
}

Symbol getSymbolInTableByName(Symbol_table *table, char *symbolName){
    return table->s[hash(symbolName)];
}

int isSymbolInTable(Symbol_table *table, char *symbol_name){   
    return table->size > hash(symbol_name) && 
    table->s[hash(symbol_name)].symbol_name != NULL && 
    !strcmp(table->s[hash(symbol_name)].symbol_name, symbol_name);
}

static int realloc_table(Symbol_table *table, unsigned long hashkey){
    Symbol *s;
    int i;
    if(table->size <= hashkey){
        long int old_size = table->size;
        table->size += hashkey;
        if(!(s = (Symbol*)realloc(table->s, (sizeof(Symbol)) * table->size))){
            raiseError(-1, "Error while realloc table->symbol | size : %ld\n", table->size);
            exit(EXIT_FAILURE);
        }
        table->s = s;
        for(i = old_size; i < hashkey; i++){
            table->s[i] = calloc_symbol();
        }
    }
}

int insert_symbol_in_table(Symbol symbol, Symbol_table *table){
    Symbol *s;
    int i;
    unsigned long hashKey = hash(symbol.symbol_name);
    realloc_table(table, hashKey);
    if(table->s[hash(symbol.symbol_name)].symbol_name && !strcmp(table->s[hash(symbol.symbol_name)].symbol_name, symbol.symbol_name)){
        return 0;
    }
    else{
        table->s[hashKey] = symbol;
        table->nb_symbol += 1;
    }
    return 1;
}

int isPrimLabelNode(Node *n){
    switch(n->label){
        case Int:
        case Character:
            return 1;
        default:
            return 0;
    }
}

PrimType labelToPrim(label_t label){
    switch(label){
        case Int:
            return INT;
        case Character:
            return CHAR;
        default:
            return NONE;
    }
}

/* We suppose there is a var node */
Symbol_table *buildGlobalVariableSymbolTable(Node *tree){
    Symbol_table *table = newSymbolTable(GLOBAL);
    Symbol symbol;
    PrimType type;
    int currentOffset = 0, number_globals = 0;
    if (!(tree->firstChild)){
        return NULL;
    }
    Node *nodeVars = tree->firstChild; /* Node of DeclVars according to our tree */
    
    for (Node *child = nodeVars->firstChild; child; child = child->nextSibling) {
        Kind kind = VARIABLE;
        type = (strcmp("int", child->u.ident) == 0) ? INT : CHAR;
        for(Node *grandChild = child->firstChild; grandChild; grandChild = grandChild->nextSibling){
            Symbol s = create_symbol(grandChild->u.ident, kind, type, currentOffset, grandChild->lineno);
            insert_symbol_in_table(s, table);

            number_globals += 1;
            currentOffset += 8;
        }
    }
    table->total_size = number_globals;
    
    
    return table;
}



void print_symbol_table(Symbol_table *tab){
    int pos;
    if(tab == NULL){
        printf("NULL \n");
        return;
    }

    fprintf(stderr,"Tab Name : %s\n",tab->name_table);
    fprintf(stderr,"nb symbol : %d\n",tab->nb_symbol);
    for(pos = 0; pos < tab->size;pos++){
        if(tab->s[pos].symbol_name == NULL) continue;;
        printf("%s\n", tab->s[pos].symbol_name);
        print_symbol(tab->s[pos]);
        
    }
}

