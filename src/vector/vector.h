#pragma once

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct _Vector {
    int *items;
    int capacity;
    int size;
} *Vector;

Vector vector_create(int capacity);
void vector_destroy(Vector vec);
void *vector_get(Vector vec, int index);
void vector_set(Vector vec, int index, const int *value);
void vector_push(Vector vec, const int *value);
void *vector_pop(Vector vec);
int vector_size(Vector vec);
int vector_capacity(Vector vec);
void vector_resize(Vector vec, int new_capacity);
Vector vector_init_by_array(int capacity, int *array);
Vector vector_init_by_value(int capacity, int value);

//Vector init(int size, int *array) // constructor
//
//Vector init_zeros(int size) // Creates vector of zeros
//
//Vector init_ones(int size) // Creates vector of ones
//
//void add(Vector r1, Vector r2, Vector result) // Adds r1 to r2 and puts it in result
//
//void subtract(Vector r1, Vector r2, Vector result) // Subtracts r2 from r1 and puts it in result
//
//void scale(Vector r, double factor) // Scales vector by factor (multiplies all values by factor)
//
//double norm(Vector r) // Returns the norm of the vector (Square root of sum of squared values)