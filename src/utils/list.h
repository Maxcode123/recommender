#pragma once

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

typedef char *key;

typedef struct _Node {
    key k;
    void *i;
    struct _Node *next;    
} *Node;

typedef void *ListItem; // A pointer to anything can be an item.

typedef Node List; // List is abstracted as head node.

/* Node constructor; allocates memory for a Node and returns a pointer to a 
Node with the given values. */
Node node(key, ListItem);

/* Linked list constructor; returns the pointer to the head of the list with
the initialization value. */
List lst_list();

// Adds a node to the linked list.
void lst_add(Node, List*);

/* Returns a pointer to the node in the list matching the given key. If there 
is no such Node, returns NULL. */
Node lst_get(key, List);

// Clears list.
void lst_clear(List*);

// Deletes head node, points head to next node.
void lst_pop(List*);

// Returns list length
int lst_len(List);