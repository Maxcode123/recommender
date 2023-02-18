#include "vector.h"

vector_t vector_create(int capacity) {
    vector_t vec = (vector_t) malloc(sizeof(struct vector));
    if (vec == NULL) {
        return NULL;
    }
    vec->data = malloc(capacity * sizeof(void *));
    if (vec->data == NULL) {
        free(vec);
        return NULL;
    }
    vec->size = 0;
    vec->capacity = capacity;
    return vec;
}

void vector_free(vector_t vec) {
    free(vec->data);
    free(vec);
}

int vector_push_back(vector_t vec, void *value) {
    if (vec->size == vec->capacity) {
        int new_capacity = vec->capacity * 2;
        void *new_data = realloc(vec->data, new_capacity * sizeof(void *));
        if (new_data == NULL) {
            return 0;
        }
        vec->data = new_data;
        vec->capacity = new_capacity;
    }
    memcpy(vec->data + vec->size * sizeof(void *), &value, sizeof(void *));
    vec->size++;
    return 1;
}

void *vector_at(vector_t vec, int index) {
    if (index >= 0 && index < vec->size) {
        return *(void **) (vec->data + index * sizeof(void *));
    }
    return NULL;
}

int vector_size(vector_t vec) {
    return vec->size;
}

int vector_capacity(vector_t vec) {
    return vec->capacity;
}


int main() {
    vector_t vec = vector_create(10);

    int value1 = 42;
    int value2 = 123;
    char *value3 = "hello";

    vector_push_back(vec, &value1);
    vector_push_back(vec, &value2);
    vector_push_back(vec, value3);
    vector_push_back(vec, value3);
    vector_push_back(vec, value3);
    vector_push_back(vec, value3);
    vector_push_back(vec, value3);
    vector_push_back(vec, value3);
    vector_push_back(vec, value3);
    vector_push_back(vec, value3);
    vector_push_back(vec, value3); //+10

    printf("Size: %d, Capacity: %d\n", vector_size(vec), vector_capacity(vec));

    printf("Element 0: %d\n", *(int *) vector_at(vec, 0));
    printf("Element 1: %d\n", *(int *) vector_at(vec, 1));
    printf("Element 2: %s\n", (char *) vector_at(vec, 2));

    vector_free(vec);
    return 0;
}
