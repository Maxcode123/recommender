#pragma once

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct vector {
    void *data;
    int size;
    int capacity;
} *vector_t;

// Creates and returns a new vector with an initial capacity.
vector_t vector_create(int capacity);
// Frees the memory used by a vector object, including its data array.
void vector_free(vector_t vec);
// Adds a new element to the end of a vector and expands its capacity if necessary.
// Returns 1 on success and 0 on failure.
int vector_push_back(vector_t vec, void *value);
// Returns a pointer to the element at the given index in the vector's data array.
void *vector_at(vector_t vec, int index);
// Returns the number of elements in the vector.
int vector_size(vector_t vec);
// Returns the current capacity of the vector's data array.
int vector_capacity(vector_t vec);

