#pragma once

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "macros.h"

typedef struct _Vector {
    double *items;      // Pointer to the underlying array of doubles
    int capacity;       // Maximum number of elements the vector can hold before resizing
    int size;           // Current number of elements in the vector
} *Vector;

// Creates a new vector with the given initial capacity
Vector vector_create(int capacity);

// Frees the memory allocated to the vector
void vector_destroy(Vector vec);

// Returns element at the specified index in the vector
double vector_get(Vector vec, int index);

// Replaces the element at the specified index with the given value
void vector_set(Vector vec, int index, double value);

// Adds a new element to the end of the vector
void vector_push(Vector vec, double value);

// Returns the number of elements in the vector
int vector_size(Vector vec);

// Returns the maximum number of elements the vector can hold before resizing
int vector_capacity(Vector vec);

// Initializes a vector with the contents of an array of integers
Vector vector_init_by_array(int capacity, double *array);

// Initializes a vector with all elements set to a given value
Vector vector_init_by_value(int capacity, double value);

// Adds two vectors element-wise, the second vector is added to the first.
void vector_add(Vector r1, Vector r2);

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

// Merges the given vectors in the array into a single vector.
Vector vector_merge(Vector*);
