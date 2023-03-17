// #include "../src/preprocess/parser/parser.h"
// #include "../src/preprocess/vectorization.h"
// #include "../src/clustering/kmeans.h"

// compile with -O3 -funroll-loops -ftree-vectorize

#include <sys/time.h>
#include <stdlib.h>
#include "stdio.h"

#define n 12000
#define m 100
int A[n][m];
int B[m][n];
int C[n][n];

float tdiff(struct timeval *start, struct timeval *end) {
    return (end->tv_sec - start->tv_sec) + 1e-6*(end->tv_usec - start->tv_usec);
}

int main(int argc, char **argv) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            A[i][j] = rand();
            B[j][i] = rand();
        }
    }
    int s1 = n/8;
    int s2 = m/8;

    struct timeval start, end;
    gettimeofday(&start, NULL);

    for (int ih = 0; ih < n; ih += s1) {
        for (int jh = 0; jh < n; jh += s1) {
            for (int kh = 0; kh < m; kh += s2) {
                for (int il = 0; il < s1; il++) {
                    for (int kl = 0; kl < s2; kl++) {
                        for (int jl = 0; jl < s1; jl++) {
                            C[ih+il][jh+jl] += A[ih+il][kh+kl] * B[kh+kl][jh+jl];
                        }
                    }
                }
            }
        }
    }

    // for (int k = 0; k < m; k++) {
    //     for (int i = 0; i < n; i++) {
    //         for (int j = 0; j < n; j++) {
    //             C[i][j] += A[i][k] * B[k][j];
    //         }
    //     }
    // }


    gettimeofday(&end, NULL);
    printf("%0.6f\n", tdiff(&start, &end));
}
