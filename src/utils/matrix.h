#pragma once

#include "vector.h"

#include <math.h>
#include <float.h>  
#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>


typedef struct _Matrix {
    double **matrix;
    int rows;
    int cols;
} *Matrix;


struct arg_struct {
    Matrix A;
    Matrix B;
    Matrix C;
    int s1;
    int s2;
    int i1;
    int i2;
};

void _multplthread(Matrix A, Matrix B, Matrix C, int s1, int s2, int i1, int i2);
void _create_multplthread(void *args);

// Matrix constructor.
Matrix matrix(int, int);

// Inserts the transpose of the first argument to the second argument.
void transpose(Matrix, Matrix);

// Multiplies the two matrices, result is put in the third argument.
void multpl(Matrix, Matrix, Matrix, int, int);

// Creates matrix from vector array.
Matrix fromvectors(Vector*, int);

// Creates an array of vectors from given matrix.
Vector* tovectors(Matrix);

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