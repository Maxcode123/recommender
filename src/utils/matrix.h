#pragma once

#include "vector.h"

#include <math.h>
#include <stdio.h>

typedef struct _Matrix {
    int **matrix;
    int rows;
    int cols;
} *Matrix;

// Inserts the transpose of the first argument to the second argument.
void transpose(Matrix, Matrix);

// Multiplies the two matrices, result is put in the third argument.
void multpl(Matrix, Matrix, Matrix);

// Creates matrix from vector array.
Matrix fromvectors(Vector*);