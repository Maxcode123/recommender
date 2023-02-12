#include "kmeans.h"

void clustering(Vector *R, int k, int n) {
    initcentroids(R);
    int i, j;
    while (flag) {
        calccentroids();
        for (i = 0; i < n; i++) {
            for (j = 0; j < k; j ++) {
                dists[i][j] = calcdistance(R[i], centroids[j]);
            }
        }
        assignvct(); // makes flag = false if now new assignment is performed.
    }
}