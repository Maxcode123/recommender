#pragma once

#include "vector.h"

#include <math.h>
#include <stdio.h>

typedef struct _Matrix {
    double **matrix;
    int rows;
    int cols;
} *Matrix;


// Matrix constructor.
Matrix matrix(int, int);

// Inserts the transpose of the first argument to the second argument.
void transpose(Matrix, Matrix);

// Multiplies the two matrices, result is put in the third argument.
void multpl(Matrix, Matrix, Matrix, int, int);

// Creates matrix from vector array.
Matrix fromvectors(Vector*, int);

// Calculate eigenvalues and eigenvectors of symmetric matrix.
void eigen(double *, double *, double*, int);