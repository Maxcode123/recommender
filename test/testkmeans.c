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
    initcentroids(R, 3);
    Vector *c = getcentroids();
    cr_assert(vector_eq(c[0], R[0]));
    cr_assert(vector_eq(c[1], R[1]));
    cr_assert(vector_eq(c[2], R[2]));
}


Test(testkmeans, testcalccentroids) {
    int k = 2;
    int n = 4;
    int d = 2;

    Vector *R = malloc(sizeof(*R) * n);
    int r1[] = {2, 7};
    int r2[] = {8, 3};
    int r3[] = {-3, -3};
    int r4[] = {-5, -12};
    R[0] = vector_init_by_array(d, r1);
    R[1] = vector_init_by_array(d, r2);
    R[2] = vector_init_by_array(d, r3);
    R[3] = vector_init_by_array(d, r4);

    initclusters(n);
    initcentroids(R, k);
    int *c = getclusters();
    c[0] = 0;
    c[1] = 0;
    c[2] = 1;
    c[3] = 1;

    calccentroids(R, k, n);

    Vector *cnr = getcentroids();
    cr_assert(vector_get(cnr[0], 0) == 5, "%d != 5", vector_get(cnr[0], 0));
    cr_assert(vector_get(cnr[0], 1) == 5, "%d != 5", vector_get(cnr[0], 1));
    cr_assert(vector_get(cnr[1], 0) == -4, "%d != -4", vector_get(cnr[1], 0));
    cr_assert(vector_get(cnr[1], 1) == -7, "%d != -7", vector_get(cnr[1], 1));
}


Test(testkmeans, testassignvct) {
    int k = 2;
    int n = 3;
    initclusters(n);
    initdists(k, n);
    double **d = getdists();
    d[0][0] = 7;
    d[0][1] = 4;
    d[0][2] = 2;
    d[1][0] = 3;
    d[1][1] = 5;
    d[1][2] = 1;
    assignvct(k, n);
    int *c = getclusters();
    cr_assert(c[0] == 1);
    cr_assert(c[1] == 0);
    cr_assert(c[2] == 1);
}


Test(testkmeans, test2dclustering) {
    int k = 2;
    int n = 4;
    int d = 2;
    Vector *R = malloc(sizeof(*R) * n);
    int r1[] = {3, 3};
    int r2[] = {4, 4};
    int r3[] = {-3, -3};
    int r4[] = {-4, -4};
    R[0] = vector_init_by_array(d, r1);
    R[1] = vector_init_by_array(d, r2);
    R[2] = vector_init_by_array(d, r3);
    R[3] = vector_init_by_array(d, r4);

    clustering(R, k, n);
    int *c = getclusters();
    cr_assert(c[0] == c[1], "R1 cluster: %d != R2 cluster: %d", c[0], c[1]);
    cr_assert(c[0] != c[3], "R1 cluster: %d == R4 cluster: %d", c[0], c[3]);
    cr_assert(c[2] == c[3], "R3 cluster: %d != R4 cluster: %d", c[2], c[3]);
}



Test(testkmeans, test3dclustering) {
    int k = 2;
    int n = 4;
    int d = 3;
    Vector *R = malloc(sizeof(*R) * n);
    int r1[] = {3, 3, 3};
    int r2[] = {4, 4, 4};
    int r3[] = {-3, -3, -3};
    int r4[] = {-4, -4, -4};
    R[0] = vector_init_by_array(d, r1);
    R[1] = vector_init_by_array(d, r2);
    R[2] = vector_init_by_array(d, r3);
    R[3] = vector_init_by_array(d, r4);

    clustering(R, k, n);
    int *c = getclusters();
    cr_assert(c[0] == c[1], "R1 cluster: %d != R2 cluster: %d", c[0], c[1]);
    cr_assert(c[0] != c[3], "R1 cluster: %d == R4 cluster: %d", c[0], c[3]);
    cr_assert(c[2] == c[3], "R3 cluster: %d != R4 cluster: %d", c[2], c[3]);
}
