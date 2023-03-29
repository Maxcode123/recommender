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


void _create_multplthread(void *args) {
    struct arg_struct *vals = args;
    _multplthread(vals->A, vals->B, vals->C, vals->s1, vals->s2, vals->i1, vals->i2);
    pthread_exit(NULL);
}

void _multplthread(Matrix A, Matrix B, Matrix C, int s1, int s2, int i1, int i2) {
    for (int ih = i1; ih < i2; ih += s1) {
        for (int jh = 0; jh < A->rows; jh += s1) {
            for (int kh = 0; kh < A->cols; kh += s2) {
                for (int il = 0; il < s1; il++) {
                    for (int kl = 0; kl < s2; kl++) {
                        for (int jl = 0; jl < s1; jl++) {
                            C->matrix[ih+il][jh+jl] += A->matrix[ih+il][kh+kl] * B->matrix[jh+jl][kh+kl];
                        }
                    }
                }
            }
        }
    }
}


void multpltransp(Matrix A, Matrix B, Matrix C, int s1, int s2) {
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
    pthread_t threads[23];
    for (int i = 0; i < 23; i++) {
        struct arg_struct thread_args;
        thread_args.A = A;
        thread_args.B = B;
        thread_args.C = C;
        thread_args.s1 = s1;
        thread_args.s2 = s2;
        thread_args.i1 = i * 50;
        thread_args.i2 = (i + 1)*50;
        int rc = pthread_create(&threads[i], NULL, _create_multplthread, (void*)&thread_args);
        if (rc) return -1;
    }
    for (int i = 0; i < 23; i++) pthread_join(threads[i], NULL);
    
    // for (int ih = 0; ih < A->rows; ih += s1) {
    //     for (int jh = 0; jh < A->rows; jh += s1) {
    //         for (int kh = 0; kh < A->cols; kh += s2) {
    //             for (int il = 0; il < s1; il++) {
    //                 for (int kl = 0; kl < s2; kl++) {
    //                     for (int jl = 0; jl < s1; jl++) {
    //                         C->matrix[ih+il][jh+jl] += A->matrix[ih+il][kh+kl] * B->matrix[jh+jl][kh+kl];
    //                     }
    //                 }
    //             }
    //         }
    //     }
    // }
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


float tdiff(struct timeval *start, struct timeval *end) {
    return (end->tv_sec - start->tv_sec) + 1e-6*(end->tv_usec - start->tv_usec);
}

void eigen(Vector *eigvecs, Matrix A) {

    struct timeval start, end;
    const int N = 50;
    int n = A->rows;
    Matrix Q = matrix(n, n);
    Matrix P = matrix(n, n);
    Matrix temp = matrix(n, n);
    double tolerance = 0.0001; // Tolerance level
    double max_off_diag = 1.0;
    double off_diag, theta, c, s;
    int p = 0, q = 1, count = 0;

    // Initialize P and Q to the identity matrix
    for(int i=0; i < n; i++)
    {
        for(int j=0; j < n; j++)
        {
            if(i == j) {
                Q->matrix[i][j] = 1.0;
                P->matrix[i][j] = 1.0;
            }
            else {
                Q->matrix[i][j] = 0.0;
                P->matrix[i][j] = 0.0;
            }

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
                off_diag = fabs(A->matrix[i][j]);
                if(off_diag > max_off_diag)
                {
                    max_off_diag = off_diag;
                    P->matrix[p][p] = 1.0;
                    P->matrix[q][q] = 1.0;
                    P->matrix[p][q] = 0.0;
                    P->matrix[q][p] = 0.0;
                    p = i;
                    q = j;
                }
            }
        }

    // Compute the Jacobi rotation matrix
        theta = 0.5 * atan2(2*A->matrix[p][q], A->matrix[q][q]-A->matrix[p][p]);
        c = cos(theta);
        s = sin(theta);

        // for(int i=0; i<n; i++)
        // {
        //     for(int j=0; j<n; j++)
        //     {
        //         if(i == j)
        //             P->matrix[i][j] = 1.0;
        //         else
        //             P->matrix[i][j] = 0.0;
        //     }
        // }
        P->matrix[p][p] = c;
        P->matrix[q][q] = c;
        P->matrix[p][q] = -s;
        P->matrix[q][p] = s;

        // Update the matrices A and Q
        gettimeofday(&start, NULL);
        multpl(P, A, temp, N, N);
        gettimeofday(&end, NULL);
        printf("T=P*A: %0.6f\n", tdiff(&start, &end));
        // for(int i=0; i<n; i++)
        // {
        //     for(int j=0; j<n; j++)
        //     {
        //         temp->matrix[i][j] = 0.0;
        //         for(int k=0; k<n; k++)
        //         {
        //             temp->matrix[i][j] += P->matrix[i][k] * A->matrix[k][j];
        //         }
        //     }
        // }
        gettimeofday(&start, NULL);
        multpltransp(temp, P, A, N, N);
        gettimeofday(&end, NULL);
        printf("A=P*A': %0.6f\n", tdiff(&start, &end));
        // for(int i=0; i<n; i++)
        // {
        //     for(int j=0; j<n; j++)
        //     {
        //         A->matrix[i][j] = 0.0;
        //         for(int k=0; k<n; k++)
        //         {
        //             A->matrix[i][j] += temp->matrix[i][k] * P->matrix[j][k];
        //         }
        //     }
        // }
        gettimeofday(&start, NULL);
        multpltransp(Q, P, temp, N, N);
        gettimeofday(&end, NULL);
        printf("Q=P*T': %0.6f\n", tdiff(&start, &end));
        // for(int i=0; i<n; i++)
        // {
        //     for(int j=0; j<n; j++)
        //     {
        //         temp->matrix[i][j] = 0.0;
        //         for(int k=0; k<n; k++)
        //         {
        //             temp->matrix[i][j] += Q->matrix[i][k] * P->matrix[j][k];
        //         }
        //     }
        // }
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                Q->matrix[i][j] = temp->matrix[i][j];
            }
        }
    printf("%f %d\n",max_off_diag, count++);    
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            vector_push(eigvecs[i], Q->matrix[j][i]);
        }
    }
    free(Q);
    free(P);
    free(temp);
}