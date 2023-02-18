#pragma  once

#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct _Node {
    void *value;
    struct _Node *next;
} *Node;
/* Initialize a new LinkedList*/
Node ll_init(void *value);
/* Adds a new value to the LinkedList */
void ll_add(Node head, void *value);
/* Removes an existing value to the LinkedList */
void ll_remove(Node* head, void* value);
/* Print all the values of the LinkedList by type*/
void ll_print_all_type(Node head,char type);
/*Gets the size of the LinkedList*/
int ll_size(Node head);