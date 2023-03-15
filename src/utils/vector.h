#pragma once

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

typedef struct _Vector {
    int *items;         // Pointer to the underlying array of integers
    int capacity;       // Maximum number of elements the vector can hold before resizing
    int size;           // Current number of elements in the vector
} *Vector;

// Creates a new vector with the given initial capacity
Vector vector_create(int capacity);

// Frees the memory allocated to the vector
void vector_destroy(Vector vec);

// Returns a pointer to the element at the specified index in the vector
int vector_get(Vector vec, int index);

// Replaces the element at the specified index with the given value
void vector_set(Vector vec, int index, int value);

// Adds a new element to the end of the vector
void vector_push(Vector vec, int value);

// Removes and returns the last element in the vector
int vector_pop(Vector vec);

// Returns the number of elements in the vector
int vector_size(Vector vec);

// Returns the maximum number of elements the vector can hold before resizing
int vector_capacity(Vector vec);

// Resizes the vector to have the specified new capacity
void vector_resize(Vector vec, int new_capacity);

// Initializes a vector with the contents of an array of integers
Vector vector_init_by_array(int capacity, int *array);

// Initializes a vector with all elements set to a given value
Vector vector_init_by_value(int capacity, int value);

// Adds two vectors element-wise and returns the resulting vector
Vector vector_add(Vector r1, Vector r2);

// Subtracts two vectors element-wise and returns the resulting vector
Vector vector_subtract(Vector r1, Vector r2);

// Scales the vector by the given factor (multiplies all elements by factor)
void vector_scale(Vector r, double factor);

// Returns the norm of the vector (square root of sum of squared values)
double vector_norm(Vector r);

// Equality comparison between two vectors.
bool vector_eq(Vector, Vector);

// Prints the contents of the vector to stdout
void vector_print(Vector vec);
