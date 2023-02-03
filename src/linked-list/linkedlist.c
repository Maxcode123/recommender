#include "linkedlist.h"
#include "stdio.h"

typedef struct Node {
    int value;
    _Node *next;
} _Node;

void print_all_linkedlist(_Node *head) {
    _Node *temp = head;
    if (temp == NULL) {
        printf("Empty list!\n");
    }
    printf("--------------\n");
    int p = 0;
    while (temp != NULL) {
        printf(".%d) %d\n", p++, temp->value);
        temp = (_Node *) temp->next;
    }
    printf("--------------\n");
}

void add_linkedlist(struct Node **head, int new_value) {
    _Node *newNode = malloc(sizeof(_Node));
    newNode->value = new_value;
    newNode->next = *head;
    *head = newNode;
}

int search_by_value_linkedlist(_Node *head, int value) {
    _Node *current = head;
    int counter = 0;
    while (head != NULL) {
        if (current->value == value) {
            return counter;
        }
        current = (_Node *) current->next;
        counter++;
    }
    return -1;
}

void sort_elements_linkedlist(_Node *head) {
    int swapped, i;
    _Node *node1, *node2 = NULL;

    if (head == NULL) {
        return;
    }

    do {
        swapped = 0;
        node1 = head;

        while (node1->next != node2) {
            if (node1->value > node1->next->value) {
                private_swap_linkedlist(node1, node1->next);
                swapped = 1;
            }
            node1 = node1->next;
        }
        node2 = node1;
    } while (swapped);
}

void private_swap_linkedlist(_Node *node1, _Node *node2) {
    int temp = node1->value;
    node1->value = node2->value;
    node2->value = temp;
}

int get_size_linkedlist(_Node *head) {
    int count = 0;
    _Node *temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

void delete_by_value_linkedlist(_Node **head, int key) {
    _Node *temp = *head, *prev;

    if (temp != NULL && temp->value == key) {
        *head = temp->next;
        free(temp);
        return;
    }

    while (temp != NULL && temp->value != key) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) return;

    prev->next = temp->next;

    free(temp);
}