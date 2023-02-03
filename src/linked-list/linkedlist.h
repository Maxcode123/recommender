#pragma  once

#include <malloc.h>

typedef struct Node _Node;

extern void print_all_linkedlist(_Node *head);

extern void add_linkedlist(struct Node** head,int new_value);

extern int search_by_value_linkedlist(_Node *head, int value);

extern void delete_by_value_linkedlist(struct Node **head_ref, int key);

extern void private_swap_linkedlist(_Node *node1, _Node *node2);

extern void sort_elements_linkedlist(_Node* head);

extern int get_size_linkedlist(_Node* head);

