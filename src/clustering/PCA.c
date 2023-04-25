#include "PCA.h"


void PCA(Matrix *m, int n) {
    Matrix T = matrix((*m)->cols, (*m)->rows); // transpose matrix
    transpose(*m, T);
    printf("made transpose T\n");
    
    Matrix Z = matrix(T->rows, (*m)->cols); // covariance matrix
    multpl(T, *m, Z, 50, 438);
    printf("Multiplied Txm\n");
    
    Vector *E = malloc(sizeof(*E)*Z->rows); // eigenvector array
    for (int i = 0; i < Z->rows; i++) E[i] = vector_create(Z->cols);

    eigen(E, Z);
    printf("calculated eigenvalues\n");
    
    double *eigenvals = malloc(sizeof(double)*Z->cols);
    int *ind = malloc(sizeof(int)*n);
    for (int i = 0; i < Z->cols; i++) eigenvals[i] = Z->matrix[i][i];
    indeces(eigenvals, Z->cols, ind, n);

    Matrix E2 = reduce(fromvectors(E, Z->rows), ind, n);

    Matrix tmp = matrix((*m)->rows, E2->cols);
    multpl(*m, E2, tmp, 876, 1);
    free(*m);
    free(ind);
    *m = tmp;
}

int compare(const void *a, const void *b) {
    return *(double*)b - *(double*)a;
}

Matrix reduce(Matrix E, int *ind, int n) {
    Matrix E2 = matrix(E->rows, n);
    for (int i = 0; i < E->rows; i++) {
        for (int j = 0; j < n; j++) {
            E2->matrix[i][j] = E->matrix[i][ind[j]];
        }
    }
    return E2;
}

void indeces(double *arr, int N, int *ind, int n) {
    int c = 0;
    double copy[N];
    for (int i = 0; i < N; i++) copy[i] = arr[i];
    qsort(arr, N, sizeof(double), compare);
    while (c < n) {
        for (int i = 0; i < N; i++) {
            if (arr[c] == copy[i]) ind[c++] = i;
        }
    }    
}

void write2dvecs(Matrix m, char *fname) {
    FILE *write;
    if (!(write = fopen(fname, "w"))) {
        fprintf(stderr, "cannot open 2d plot write file\n");
        exit(1);
    }
    for (int i = 0; i < m->rows; i++) {
        fprintf(write, "%f %f\n", m->matrix[i][0], m->matrix[i][1]);
    }
    fclose(write);
}