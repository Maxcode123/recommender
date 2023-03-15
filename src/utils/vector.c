#include "vector.h"

Vector vector_create(int capacity) {
    Vector vec = malloc(sizeof(struct _Vector));
    if (vec == NULL) {
        fprintf(stderr, "Error: Out of memory.\n");
        exit(EXIT_FAILURE);
    }
    vec->capacity = capacity;
    vec->size = 0;
    vec->items = malloc(capacity * sizeof(int));
    if (vec->items == NULL) {
        free(vec);
        fprintf(stderr, "Error: Out of memory.\n");
        exit(EXIT_FAILURE);
    }
    return vec;
}

void vector_destroy(Vector vec) {
    free(vec->items);
    free(vec);
}

int vector_get(Vector vec, int index) {
    if (index < 0 || index >= vec->size) {
        return NULL;
    }
    return vec->items[index];
}

void vector_set(Vector vec, int index, int value) {
    if (index < 0 || index >= vec->size) {
        return;
    }
    vec->items[index] = value;
}

void vector_push(Vector vec, int value) {
    if (vec->size >= vec->capacity) {
        vector_resize(vec, vec->capacity * 2);
    }
    vec->items[vec->size] = value;
    vec->size++;
}

int vector_pop(Vector vec) {
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
    void **new_items = malloc(new_capacity * sizeof(int *));
    if (new_items == NULL) {
        fprintf(stderr, "Error: Out of memory.\n");
        exit(EXIT_FAILURE);
    }
    memcpy(new_items, vec->items, vec->size * sizeof(int *));
    free(vec->items);
    vec->items = new_items;
    vec->capacity = new_capacity;
}

Vector vector_init_by_array(int capacity, int *array) {
    Vector vec = vector_create(capacity);
    for (int i = 0; i < capacity; i++) {
        vector_push(vec, array[i]);
    }
    return vec;
}

Vector vector_init_by_value(int capacity, int value) {
    Vector vec = vector_create(capacity);
    for (int i = 0; i < capacity; i++) {
        vector_push(vec, value);
    }
    return vec;
}

Vector vector_add(Vector r1, Vector r2) {
    if (r1->size != r2->size) {
        printf("Error: Vectors are not of the same size.\n");
        exit(EXIT_FAILURE);
    }

    Vector result = vector_create(r1->size);
    for (int i = 0; i < r1->size; i++) {
        int x = r1->items[i] + r2->items[i];
        vector_push(result, x);
    }
    return result;
}

Vector vector_subtract(Vector r1, Vector r2) {
    if (r1->size != r2->size) {
        fprintf(stderr, "Error: Vectors are not of the same size.\n");
        exit(EXIT_FAILURE);
    }

    Vector result = vector_create(r1->size);
    for (int i = 0; i < r1->size; i++) {
        int x = r1->items[i] - r2->items[i];
        vector_push(result, x);
    }
    return result;
}

void vector_print(Vector vec) {
    printf("[");
    for (int i = 0; i < vec->size; i++) {
        printf("%d", vec->items[i]);
        if (i < vec->size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

void vector_scale(Vector r, double factor) {
    for (int i = 0; i < r->size; i++) {
        r->items[i] = (int) (r->items[i] * factor);
    }
}

double vector_norm(Vector r) {
    double sum_of_squares = 0.0;
    for (int i = 0; i < r->size; i++) {
        sum_of_squares += pow(r->items[i], 2);
    }
    return sqrt(sum_of_squares);
}

bool vector_eq(Vector r1, Vector r2) {
    if (vector_size(r1) != vector_size(r2)) return false;
    for (int i = 0; i < vector_size(r1); i++) {
        if (vector_get(r1, i) != vector_get(r2, i)) return false;
    }
    return true;
}