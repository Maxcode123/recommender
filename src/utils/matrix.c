#include "matrix.h"

Matrix matrix(int rows, int cols) {
    Matrix m = malloc(sizeof(*m));
    m->matrix = (double*)malloc(sizeof(double)*rows);
    for (int i = 0; i < rows; i++) {
        m->matrix[i] = (double*)malloc(sizeof(double)*cols);
    }
    m->rows = rows;
    m->cols = cols;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            m->matrix[i][j] = 0;
        }
    }
    return m;
}

void transpose(Matrix A, Matrix B) {
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->cols; j++) {
            B->matrix[j][i] = A->matrix[i][j];
        }
    }
}

void multpl(Matrix A, Matrix B, Matrix C, int s1, int s2) {
    if (A->cols != B->rows) {
        fprintf(stderr, "Invalid dimensions for matrix multiplication A(%dx%d) B(%dx%d)",
                A->rows, A->cols, B->rows, B->cols);
        exit(1);
    }
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < B->cols; j++) {
            C->matrix[i][j] = 0;
        }
    }
    for (int ih = 0; ih < A->rows; ih += s1) {
        for (int jh = 0; jh < A->rows; jh += s1) {
            for (int kh = 0; kh < A->cols; kh += s2) {
                for (int il = 0; il < s1; il++) {
                    for (int kl = 0; kl < s2; kl++) {
                        for (int jl = 0; jl < s1; jl++) {
                            C->matrix[ih+il][jh+jl] += A->matrix[ih+il][kh+kl] * B->matrix[kh+kl][jh+jl];
                        }
                    }
                }
            }
        }
    }
}

Matrix fromvectors(Vector *R, int n) {
    Matrix m = matrix(n, vector_size(R[0]));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m->cols; j++) {
            m->matrix[i][j] = R[i]->items[j];
        }   
    }
    return m;
}