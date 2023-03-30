#include "kmeans.h"

void clustering(Vector *R, int k, int n, int it) {
    initcentroids(R, k);
    initclusters(n);
    initdists(k ,n);
    assignment(R, k, n);
    flag = true;
    int c = 0;
    while (flag && c++ < it) {
        printf("%d\n", c);
        calccentroids(R, k, n);
        assignment(R, k, n);
    }
}

int *getclusters() {
    return clusters;
}

Vector *getcentroids() {
    return centroids;
}

void initclusters(int n) {
    clusters = malloc(sizeof(int) *n);
    for (int i = 0; i < n; i++) clusters[i] = 0;
}

bool getflag() {
    return flag;
}

double **getdists() {
    return dists;
}

void initdists(int k, int n) {
    dists = malloc(sizeof(double*) * k);
    for (int j = 0; j < k; j++) {
        double *tmp = malloc(sizeof(double) * n);
        for (int i = 0; i < n; i++) {
            tmp[i] = 0;
        }
        dists[j] = tmp;
    }
}

void printdists(int k, int n) {
    printf("    R1");
    for (int j = 1; j < n; j++) printf("     R%d", j + 1);
    printf("\n");
    for (int i = 0; i <k; i++) {
        printf("k%d  ", i + 1);
        for (int j = 0; j < n; j++) {
            printf("%.3f  ", dists[i][j]);
        }
        printf("\n");
    }
}

void initcentroids(Vector *R, int k) {
    if (_initcentroids == false) centroids = malloc(sizeof(*centroids)*k);
    srand(time(NULL));
    for (int i = 0; i < k; i++){
        centroids[i] = R[i];
    }
    _initcentroids = true;
}

void assignment(Vector *R, int k, int n) {
    for (int j = 0; j < k; j++) {
        for (int i = 0; i < n; i++) {
            dists[j][i] = calcd_euc(R[i], centroids[j]);
        }
    }
    assignvct(k, n); // makes flag = false if no new assignment is performed.
}

double calcd_euc(Vector R1, Vector R2) {
    double sum = 0;
    for (int i = 0; i < vector_size(R1); i++) {
        if (vector_get(R1, i) && vector_get(R2, i)) {
            sum += pow(vector_get(R1, i) - vector_get(R2, i), 2);
        }
    }
    sum = sqrt(sum);
    return sum;
}

double calcd_cos(Vector R1, Vector R2) {
    double sum_num = 0, sum_denom1 = 0, sum_denom2 = 0;
    for (int i = 0; i < vector_size(R1); i++) {
        if (vector_get(R1, i) && vector_get(R2, i)) {
            sum_num += vector_get(R1, i) * vector_get(R2, i);
            sum_denom1 += pow(vector_get(R1, i), 2);
            sum_denom2 += pow(vector_get(R2, i), 2);
        }
    }
    double d = 1 - (sum_num / sqrt(sum_denom1 * sum_denom2));
    return d;    
}

void assignvct(int k, int n) {
    int i, j, c;
    double min;
    flag = false;
    for (i = 0; i < n; i++) {
        min = dists[clusters[i]][i];
        c = clusters[i];
        for (j = 1; j < k; j++) {
            if (dists[j][i] < min) {
                min = dists[j][i];
                if (clusters[i] != j) {
                    c = j;
                    flag = true;
                }
            }
        }
        clusters[i] = c;
    }
}

void calccentroids(Vector *R, int k, int n) {
    Vector *sums = malloc(sizeof(*sums)*k);
    int counts[k];
    int d = vector_size(R[0]); // dimensions of vectors
    for (int i = 0; i < k; i++) {
        counts[i] = 0;
        sums[i] = vector_init_by_value(d, 0);
    }
    for (int j = 0; j < n; j++) {
        vector_add(sums[clusters[j]], R[j]);
        counts[clusters[j]]++;
    }
    for (int p = 0; p < k; p++) {
        double factor = 1.0/counts[p];
        vector_scale(sums[p], factor);
    }
    free(centroids);
    centroids = sums;   
}