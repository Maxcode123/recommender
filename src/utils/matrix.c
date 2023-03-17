#include "matrix.h"

void multpl(Matrix A, Matrix B, Matrix C) {
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
    
    int s1 = A->rows/8; // tile horizontal dimension
    int s2 = A->cols/8; // tile vertical dimension

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