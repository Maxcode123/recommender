#include "matrix.h"

Matrix matrix(int rows, int cols) {
    Matrix m = malloc(sizeof(*m));
    m->matrix = (double**)malloc(sizeof(double*)*rows);
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

Matrix rowvec(Vector R) {
    Matrix m = matrix(1, vector_size(R));
    for (int i = 0; i < m->cols; i++) {
        m->matrix[0][i] = R->items[i];
    }
    return m;
}

Matrix colvec(Vector R) {
    Matrix m = matrix(vector_size(R), 1);
    for (int i = 0; i < m->rows; i++) {
        m->matrix[i][0] = R->items[i];
    }
    return m;
}

void matrix_print(Matrix m) {
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            printf("%f    ", m->matrix[i][j]);
        }
        printf("\n");
    }
}

Matrix matrix_copy(Matrix m) {
    Matrix new = matrix(m->rows, m->cols);
    for (int i = 0 ; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            new->matrix[i][j] = m->matrix[i][j];
        }
    }
    return new;
}

void eigen(double *eigvals, Vector *eigvecs, Matrix A) {
    
    int n = A->rows;
    double Q[n][n];
    double tolerance = 1e-10; // Tolerance level
    double max_off_diag = 1.0;
    int p, q, count = 0;

    // Initialize Q to the identity matrix
    for(int i=0; i < n; i++)
    {
        for(int j=0; j < n; j++)
        {
            if(i == j)
                Q[i][j] = 1.0;
            else
                Q[i][j] = 0.0;
        }
    }

    while(max_off_diag > tolerance)
    {
        // Find the maximum off-diagonal element
        max_off_diag = 0.0;
        for(int i=0; i<n; i++)
        {
            for(int j=i+1; j<n; j++)
            {
                double off_diag = fabs(A->matrix[i][j]);
                if(off_diag > max_off_diag)
                {
                    max_off_diag = off_diag;
                    p = i;
                    q = j;
                }
            }
        }

    // Compute the Jacobi rotation matrix
        double theta = 0.5 * atan2(2*A->matrix[p][q], A->matrix[q][q]-A->matrix[p][p]);
        double c = cos(theta);
        double s = sin(theta);

        double P[n][n];
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                if(i == j)
                    P[i][j] = 1.0;
                else
                    P[i][j] = 0.0;
            }
        }
        P[p][p] = c;
        P[q][q] = c;
        P[p][q] = -s;
        P[q][p] = s;

        // Update the matrices A and Q
        double temp[n][n];
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                temp[i][j] = 0.0;
                for(int k=0; k<n; k++)
                {
                    temp[i][j] += P[i][k] * A->matrix[k][j];
                }
            }
        }
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                A->matrix[i][j] = 0.0;
                for(int k=0; k<n; k++)
                {
                    A->matrix[i][j] += temp[i][k] * P[j][k];
                }
            }
        }
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                temp[i][j] = 0.0;
                for(int k=0; k<n; k++)
                {
                    temp[i][j] += Q[i][k] * P[j][k];
                }
            }
        }
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                Q[i][j] = temp[i][j];
            }
        }
    count++;    
    }
    for (int i = 0; i < n; i++) {
        eigvals[i] = A->matrix[i][i];
        for (int j = 0; j < n; j++) {
            vector_push(eigvecs[i], Q[j][i]);
        }
    }
}