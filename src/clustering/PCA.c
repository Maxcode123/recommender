#include "PCA.h"


void PCA(Matrix m, int n) {
    Matrix t = matrix(m->rows, m->cols);
    transpose(m, t);
    
    Matrix Z = matrix(m->rows, m->rows); // covariance matrix
    multpl(m, t, Z, m->rows/2, t->cols/2);
    
    double eigenvalues[Z->rows], eigenvectors[Z->rows][Z->rows];
    eigen(eigenvalues, (double*)eigenvectors, (double*)Z->matrix, Z->rows);

    // sort eigenvectors based on eigenvalues
    // choose n first eigenvectors
    // transpose eigenvectors
    // multiply by t
    // assign result to m
}