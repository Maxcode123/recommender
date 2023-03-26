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

void eigen(double *eigvals, Vector **eigvecs, Matrix M) {
    double *eigenvectors = malloc(sizeof(double)*M->rows*M->cols);
    int n = M->cols;
    double _A[n][n];
    for (int i = 0; i < M->rows; i++) {
        for (int j = 0; j < M->cols; j++) {
            _A[i][j] = M->matrix[i][j];
        }
    }
    double *A = _A;


    int row, i, j, k, m;
    double *pAk, *pAm, *p_r, *p_e;
    double threshold_norm;
    double threshold;
    double tan_phi, sin_phi, cos_phi, tan2_phi, sin2_phi, cos2_phi;
    double sin_2phi, cos_2phi, cot_2phi;
    double dum1;
    double dum2;
    double dum3;
    double r;
    double max;

                    // Take care of trivial cases

    if ( n < 1) return;
    if ( n == 1) {
        eigvals[0] = *A;
        *eigenvectors = 1.0;
        return;
    }

    for (p_e = eigenvectors, i = 0; i < n; i++)
      for (j = 0; j < n; p_e++, j++)
         if (i == j) *p_e = 1.0; else *p_e = 0.0;
  
            // Calculate the threshold and threshold_norm.

    for (threshold = 0.0, pAk = A, i = 0; i < ( n - 1 ); pAk += n, i++) 
      for (j = i + 1; j < n; j++) threshold += *(pAk + j) * *(pAk + j);
   threshold = sqrt(threshold + threshold);
   threshold_norm = threshold * DBL_EPSILON;
   max = threshold + 1.0;
   while (threshold > threshold_norm) {
      threshold /= 10.0;
      if (max < threshold) continue;
      max = 0.0;
      for (pAk = A, k = 0; k < (n-1); pAk += n, k++) {
         for (pAm = pAk + n, m = k + 1; m < n; pAm += n, m++) {
            if ( fabs(*(pAk + m)) < threshold ) continue;

                 // Calculate the sin and cos of the rotation angle which
                 // annihilates A[k][m].

            cot_2phi = 0.5 * ( *(pAk + k) - *(pAm + m) ) / *(pAk + m);
            dum1 = sqrt( cot_2phi * cot_2phi + 1.0);
            if (cot_2phi < 0.0) dum1 = -dum1;
            tan_phi = -cot_2phi + dum1;
            tan2_phi = tan_phi * tan_phi;
            sin2_phi = tan2_phi / (1.0 + tan2_phi);
            cos2_phi = 1.0 - sin2_phi;
            sin_phi = sqrt(sin2_phi);
            if (tan_phi < 0.0) sin_phi = - sin_phi;
            cos_phi = sqrt(cos2_phi); 
            sin_2phi = 2.0 * sin_phi * cos_phi;
            cos_2phi = cos2_phi - sin2_phi;

                     // Rotate columns k and m for both the matrix A 
                     //     and the matrix of eigenvectors.

            p_r = A;
            dum1 = *(pAk + k);
            dum2 = *(pAm + m);
            dum3 = *(pAk + m);
            *(pAk + k) = dum1 * cos2_phi + dum2 * sin2_phi + dum3 * sin_2phi;
            *(pAm + m) = dum1 * sin2_phi + dum2 * cos2_phi - dum3 * sin_2phi;
            *(pAk + m) = 0.0;
            *(pAm + k) = 0.0;
            for (i = 0; i < n; p_r += n, i++) {
               if ( (i == k) || (i == m) ) continue;
               if ( i < k ) dum1 = *(p_r + k); else dum1 = *(pAk + i);
               if ( i < m ) dum2 = *(p_r + m); else dum2 = *(pAm + i);
               dum3 = dum1 * cos_phi + dum2 * sin_phi;
               if ( i < k ) *(p_r + k) = dum3; else *(pAk + i) = dum3;
               dum3 = - dum1 * sin_phi + dum2 * cos_phi;
               if ( i < m ) *(p_r + m) = dum3; else *(pAm + i) = dum3;
            }
            for (p_e = eigenvectors, i = 0; i < n; p_e += n, i++) {
               dum1 = *(p_e + k);
               dum2 = *(p_e + m);
               *(p_e + k) = dum1 * cos_phi + dum2 * sin_phi;
               *(p_e + m) = - dum1 * sin_phi + dum2 * cos_phi;
            }
         }
         for (i = 0; i < n; i++)
            if ( i == k ) continue;
            else if ( max < fabs(*(pAk + i))) max = fabs(*(pAk + i));
      }
   }
   for (pAk = A, k = 0; k < n; pAk += n, k++) eigvals[k] = *(pAk + k);

   for (int i = 0; i < n; i++) {
    Vector v = vector_create(n);
    for (int j = 0; j < n; j++, eigenvectors++) {
        vector_push(v, *eigenvectors);
    }
    (*eigvecs)[i] = v;
   }
//    free(eigenvectors);
}

void eigen2(double *eigvals, Vector *eigvecs, Matrix A) {
    
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