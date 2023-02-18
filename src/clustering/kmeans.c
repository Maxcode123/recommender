#include "kmeans.h"

void clustering(Vector *R, int k, int n) {
    initcentroids(R, k, n);
    int i, j;
    while (flag) {
        calccentroids(R, k, n);
        for (i = 0; i < n; i++) {
            for (j = 0; j < k; j ++) {
                dists[i][j] = calcdistance(R[i], centroids[j]);
            }
        }
        assignvct(k, n); // makes flag = false if no new assignment is performed.
    }
}

int *getclusters() {
    return clusters;
}

void initcentroids(Vector *R, int k, int n) {
    if (_initcentroids == false) centroids = malloc(sizeof(*centroids)*k);
    srand(time(NULL));
    for (int i = 0; i < k; i++){
        centroids[i] = R[rand() % n];
    }
    _initcentroids = true;
}

double calcdistance(Vector R1, Vector R2) {
    double sum = 0;
    for (int i = 0; i < R1->size; i++) {
        if (R1->values[i] && R2->values[i]) sum += pow(R1->values[i] - R2->values[i], 2);
    }
    sum = sqrt(sum);
    return sum;
}

void assignvct(int k, int n) {
    int i, j, min;
    for (i = 0; i < n; i++) {
        min = 0;
        for (j = 1; j < k; j++) {
            if (dists[i][j] < dists[i][j-1]) min = j;
        }
        clusters[i] = min;
    }
}

void calccentroids(Vector *R, int k, int n) {
    Vector *sums = malloc(sizeof(*sums)*k);
    int counts[k];
    for (int i = 0; i < k; i++) {
        counts[i] = 0;
        sums[i] = vct_zeros(n);
    }
    for (int j = 0; j < n; j++) {
        vct_add(R[j], sums[clusters[j]], sums[clusters[j]]);
        counts[clusters[j]]++;
    }
    for (int p = 0; p < k; p++) {
        vct_scale(sums[p], 1/counts[p]);
    }
    free(centroids);
    centroids = sums;   
}