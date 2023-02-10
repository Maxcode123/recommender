#include "list.h"

Node node(key k, ListItem i) {
    Node n = (Node)malloc(sizeof(*n));
    n->k = k;
    n->i = i;
    n->next = NULL;
    return n;
}

List lst_list() {
    return NULL;
}

void lst_add(Node n, List* headptr) {
    if (*headptr == NULL)
    {
        *headptr = n;
        n->next = NULL;
    }
    else
    {
        n->next = *headptr;
        *headptr = n;
    }
}

Node lst_get(key k, List head) {
    Node n = head;
    while (n != NULL)
    {
        if (strcmp(n->k, k) == 0) return n;
        n = n->next;
    }
    return NULL;
}

void lst_clear(List *headptr) {
    while (*headptr != NULL) lst_pop(headptr);
}

void lst_pop(List *headptr) {
    Node tmp = (*headptr)->next;
    free(*headptr);
    *headptr = tmp;
}

int lst_len(List head) {
    Node n = head;
    int c = 0;
    while (n != NULL)
    {
        c++;
        n = n->next;
    }
    return c;
}