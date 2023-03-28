#pragma once

#include "vector.h"

#include <math.h>
#include <float.h>  
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>


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

// Creates a 1xn matrix where n is the size of the given vector.
Matrix rowvec(Vector);

// Creates a nx1 matrixwhere n is the size of the given vector.
Matrix colvec(Vector);

// Prints matrix in nice format.
void matrix_print(Matrix);

// Creates a copy of the given matrix.
Matrix matrix_copy(Matrix);

/* Calculates eigenvalues and eigenvectors of symmetric matrix.
Eigenvalues are inserted in the diagonal of the given matrix.
Eigenvectors are returned as an array of vectors.
MUTATES GIVEN MATRIX.
*/
void eigen(Vector*, Matrix);