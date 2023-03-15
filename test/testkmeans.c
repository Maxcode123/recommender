#include <criterion/criterion.h>

#include "../src/clustering/kmeans.h"


Test(testkmeans, testzerodist) {
    int r1[] = {3, 3};
    int r2[] = {3, 3};
    Vector R1 = vector_init_by_array(2, r1);
    Vector R2 = vector_init_by_array(2, r2);
    double d = calcdistance(R1, R2);
    cr_assert(d == 0, "%d != 0", d);
}


Test(testkmeans, testdist) {
    int r1[] = {3, 3};
    int r2[] = {6, 7};
    Vector R1 = vector_init_by_array(2, r1);
    Vector R2 = vector_init_by_array(2, r2);
    double d = calcdistance(R1, R2);
    cr_assert( d == 5, "%f != 1", d);
}


Test(testkmeans, testinitdists) {
    initdists(2, 3);
    double **d = getdists();
    for (int j = 0; j < 2; j++) {
        for (int i = 0; i < 3; i++) {
            cr_assert(d[j][i] == 0, "d[%d][%d] != 0", j, i);
        }
    }
}

Test(testkmeans, testinitcentroids) {
    Vector *R = malloc(sizeof(*R) * 4);
    int r1[] = {3, 3};
    int r2[] = {4, 4};
    int r3[] = {-3, -3};
    int r4[] = {-4, -4};
    R[0] = vector_init_by_array(2, r1);
    R[1] = vector_init_by_array(2, r2);
    R[2] = vector_init_by_array(2, r3);
    R[3] = vector_init_by_array(2, r4);
    
    // n = 1, all centroids should be assigned R[0] as value
    initcentroids(R, 3, 1);
    Vector *c = getcentroids();
    cr_assert(vector_eq(c[0], R[0]));
    cr_assert(vector_eq(c[1], R[0]));
    cr_assert(vector_eq(c[2], R[0]));
}


Test(testkmeans, testclustering) {
    Vector *R = malloc(sizeof(*R) * 4);
    int r1[] = {3, 3};
    int r2[] = {4, 4};
    int r3[] = {-3, -3};
    int r4[] = {-4, -4};
    R[0] = vector_init_by_array(2, r1);
    R[1] = vector_init_by_array(2, r2);
    R[2] = vector_init_by_array(2, r3);
    R[3] = vector_init_by_array(2, r4);

    clustering(R, 2, 4);
    int *c = getclusters();
    cr_assert(c[0] == c[1], "R1 cluster: %d != R2 cluster: %d", c[0], c[4]);
    cr_assert(c[0] != c[3], "R1 cluster: %d == R4 cluster: %d", c[0], c[3]);
    cr_assert(c[2] == c[3], "R3 cluster: %d != R4 cluster: %d", c[2], c[3]);
}
