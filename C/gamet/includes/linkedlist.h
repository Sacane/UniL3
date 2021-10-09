#ifndef __LINKEDLIST
#define __LINKEDLIST



typedef struct cell{

    int index;
    struct cell *next;

}Cell, *LinkedList;


LinkedList new_linkedList();

LinkedList li_add(LinkedList list, int value);

LinkedList li_clear(LinkedList list);



#endif