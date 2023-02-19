#include "vector.h"

Vector vector_create(int capacity) {
    Vector vec = malloc(sizeof(struct _Vector));
    if(vec == NULL){
        fprintf(stderr, "Error: Out of memory.\n");
        exit(EXIT_FAILURE);
    }
    vec->capacity = capacity;
    vec->size = 0;
    vec->items = malloc(capacity * sizeof(void *));
    if(vec->items == NULL){
        free(vec);
        fprintf(stderr, "Error: Out of memory.\n");
        exit(EXIT_FAILURE);
    }
    return vec;
}

void vector_destroy(Vector vec) {
    //todo: review it please
    for (int i = 0; i < vec->size; i++) {
        free(vec->items[i]);
    }
    free(vec->items);
    free(vec);
}

void *vector_get(Vector vec, int index) {
    if (index < 0 || index >= vec->size) {
        return NULL;
    }
    return vec->items[index];
}

void vector_set(Vector vec, int index, void *value) {
    if (index < 0 || index >= vec->size) {
        return;
    }
    vec->items[index] = value;
}

void vector_push(Vector vec, void *value) {
    if (vec->size >= vec->capacity) {
        vector_resize(vec, vec->capacity * 2);
    }
    vec->items[vec->size] = value;
    vec->size++;
}

void *vector_pop(Vector vec) {
    if (vec->size == 0) {
        return NULL;
    }
    vec->size--;
    return vec->items[vec->size];
}

int vector_size(Vector vec) {
    return vec->size;
}

int vector_capacity(Vector vec) {
    return vec->capacity;
}

void vector_resize(Vector vec, int new_capacity) {
    void **new_items = malloc(new_capacity * sizeof(void *));
    if (new_items == NULL) {
        fprintf(stderr, "Error: Out of memory.\n");
        exit(EXIT_FAILURE);
    }
    memcpy(new_items, vec->items, vec->size * sizeof(void *));
    free(vec->items);
    vec->items = new_items;
    vec->capacity = new_capacity;
}

Vector vector_init_by_array(int capacity, int *array) {
    Vector vec = vector_create(capacity);
    for (int i = 0; i < capacity; i++) {
        int *value = malloc(sizeof(int));
        if (value == NULL) {
            // Out of memory error
            fprintf(stderr, "Error: Out of memory.\n");
            exit(EXIT_FAILURE);
        }
        *value = array[i];
        vector_push(vec, value);
    }
    return vec;
}


int vector_tests() {
    int arr[] = {1,2,3,4,5};
    Vector vec = vector_init_by_array(4,arr);
    int x1 = 100;
    int x2 = 200;
    int x3 = 300;
    int x4 = 400;
    int x5 = 500;
    int x6 = 500;
    vector_push(vec,&x1);
    vector_push(vec,&x2);
    vector_push(vec,&x3);
    vector_push(vec,&x4);
    vector_push(vec,&x5);
    vector_push(vec,&x6);

    printf("Vector capacity: %d, size: %d, elements: ", vec->capacity, vec->size);
    for (int i = 0; i < vec->size; i++) {
        printf("%d ", *(int *) vec->items[i]);
    }
    printf("\n");

    printf("V:capacity -> %d\n",vector_capacity(vec));
    printf("V:capacity -> %d\n",vector_size(vec));
    printf("%d\n",*(int*)vector_get(vec,1));
    int x_5000 = 5000;
    vector_set(vec,1,&x_5000);
    printf("%d\n",*(int*)vector_get(vec,1));

    vector_pop(vec); //500
    vector_pop(vec); //500
    vector_pop(vec); //400
    vector_pop(vec); //300

    printf("Vector capacity: %d, size: %d, elements: ", vec->capacity, vec->size);
    for (int i = 0; i < vec->size; i++) {
        printf("%d ", *(int *) vec->items[i]);
    }
    printf("\n");


//    vector_destroy(vec);
    return 0;
}
