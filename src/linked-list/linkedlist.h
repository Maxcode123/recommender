#include "LinkedListImpl.h"

int ll_test_int() {
    printf("test for int\n");
    int x1 = 1000;
    int x2 = 2000;
    int x3 = 3000;
    int x4 = 4000;

    void *px1 = &x1;
    void *px2 = &x2;
    void *px3 = &x3;
    void *px4 = &x4;

    Node head_strings = ll_init(px1);
    ll_add(head_strings, px2);
    ll_add(head_strings, px3);
    ll_add(head_strings, px4);
    printf("before delete: \n");
    printf("size: %d\n", ll_size(head_strings));
    ll_print_all_type(head_strings, 'd');
    ll_remove(&head_strings, px2);
    printf("after delete: \n");
    ll_print_all_type(head_strings, 'd');
}

int ll_test_double() {
    printf("test for double\n");
    double x1 = 1000.25;
    double x2 = 2000.55;
    double x3 = 3000.45;
    double x4 = 4000.55;

    void *px1 = &x1;
    void *px2 = &x2;
    void *px3 = &x3;
    void *px4 = &x4;

    Node head_doubles = ll_init(px1);
    ll_add(head_doubles, px2);
    ll_add(head_doubles, px3);
    ll_add(head_doubles, px4);
    printf("before delete: \n");
    printf("size: %d\n", ll_size(head_doubles));
    ll_print_all_type(head_doubles, 'f');
    ll_remove(&head_doubles, px2);
    printf("after delete: \n");
    ll_print_all_type(head_doubles, 'f');
}


int ll_test_strings() {
    printf("test for strings\n");
    char* x1 = {"Hello world"};
    char* x2 = {"How are you"};
    char* x3 = {"Nikos Koukos"};
    char* x4 = {"John Smith"};

    Node head_strings = ll_init(x1);
    ll_add(head_strings, x2);
    ll_add(head_strings, x3);
    ll_add(head_strings, x4);
    printf("before delete: \n");
    printf("size: %d\n", ll_size(head_strings));
    ll_print_all_type(head_strings, 's');
    ll_remove(&head_strings, x1);
    printf("after delete: \n");
    ll_print_all_type(head_strings, 's');
}


void LinkedList() {
    ll_test_int();
    ll_test_double();
    ll_test_strings();
}

Node ll_init(void *value) {
    Node head = malloc(sizeof(struct _Node));
    head->value = value;
    head->next = NULL;
    return head;
}

void ll_add(Node head, void *value) {
    Node current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    Node new_node = malloc(sizeof(struct _Node));
    new_node->value = value;
    new_node->next = NULL;
    current->next = new_node;
}

void ll_remove(Node *head, void *value) {
    Node current = *head;
    Node prev = NULL;
    while (current != NULL) {
        if (current->value == value) {
            if (prev == NULL) {
                *head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

void ll_print_all_type(Node head, char type) {
    Node current = head;
    int wrongType = 0;
    while (current != NULL) {
        switch (type) {
            case 'd':
                printf("%d \n", *(int *) current->value);
                break;
            case 'c':
                printf("%c \n", *(char *) current->value);
                break;
            case 'f':
                printf("%.2f \n", *(double *) current->value);
                break;
            case 's':
                printf("%s \n", current->value);
                break;
            case 'p':
                printf("%p \n", (void *) current->value);
                break;
            default:
                printf("Please put a valid option: d,c,f,p \n");
                wrongType = 1;
                break;
        }
        if (wrongType == 0) {
            current = current->next;
        } else {
            current = NULL;
        }

    }
}

int ll_size(Node head) {
    int size = 0;
    Node current = head;
    while (current != NULL) {
        size++;
        current = current->next;
    }
    return size;
}


