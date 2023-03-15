#include "kmeans.h"

void clustering(Vector *R, int k, int n) {
    initcentroids(R, k, n);
    initclusters(n);
    initdists(k ,n);
    assignment(R, k, n);
    while (flag) {
        calccentroids(R, k, n);
        assignment(R, k, n);        
    }
}

int *getclusters() {
    return clusters;
}

void initclusters(int n) {
    clusters = malloc(sizeof(int) *n);
    for (int i = 0; i < n; i++) clusters[i] = 0;
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

void initcentroids(Vector *R, int k, int n) {
    if (_initcentroids == false) centroids = malloc(sizeof(*centroids)*k);
    srand(time(NULL));
    for (int i = 0; i < k; i++){
        centroids[i] = R[rand() % n];
    }
    _initcentroids = true;
}

void assignment(Vector *R, int k, int n) {
    for (int j = 0; j < k; j++) {
        for (int i = 0; i < n; i++) {
            dists[j][i] = calcdistance(R[i], centroids[j]);
        }
    }
    assignvct(k, n); // makes flag = false if no new assignment is performed.
}

double calcdistance(Vector R1, Vector R2) {
    double sum = 0;
    for (int i = 0; i < R1->size; i++) {
        if (vector_get(R1, i) && vector_get(R2, i)) sum += pow(vector_get(R1, i) - vector_get(R2, i), 2);
    }
    sum = sqrt(sum);
    return sum;
}

void assignvct(int k, int n) {
    int i, j, min;
    for (j = 1; j < k; j++) {
        min = 0;
        for (i = 0; i < n; i++) {
            if (dists[j][i] < dists[j-1][i]) min = j;
        }
        clusters[i] = min;
    }
}

void calccentroids(Vector *R, int k, int n) {
    Vector *sums = malloc(sizeof(*sums)*k);
    int counts[k];
    for (int i = 0; i < k; i++) {
        counts[i] = 0;
        sums[i] = vector_init_by_value(n, 0);
    }
    for (int j = 0; j < n; j++) {
        Vector tmp = vector_add(R[j], sums[clusters[j]]);
        free(&sums[clusters[j]]);
        sums[clusters[j]] = tmp;
        counts[clusters[j]]++;
    }
    for (int p = 0; p < k; p++) {
        vector_scale(sums[p], 1/counts[p]);
    }
    free(centroids);
    centroids = sums;   
}