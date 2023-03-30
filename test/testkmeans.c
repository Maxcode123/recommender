#include <criterion/criterion.h>

#include "../src/clustering/kmeans.h"


Test(testkmeans, testzerodist) {
    double r1[] = {3, 3};
    double r2[] = {3, 3};
    Vector R1 = vector_init_by_array(2, r1);
    Vector R2 = vector_init_by_array(2, r2);
    double d = calcd_euc(R1, R2);
    cr_assert(d == 0, "%d != 0", d);
}


Test(testkmeans, testdist) {
    double r1[] = {3, 3};
    double r2[] = {6, 7};
    Vector R1 = vector_init_by_array(2, r1);
    Vector R2 = vector_init_by_array(2, r2);
    double d = calcd_euc(R1, R2);
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
    double r1[] = {3, 3};
    double r2[] = {4, 4};
    double r3[] = {-3, -3};
    double r4[] = {-4, -4};
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
    double r1[] = {2, 7};
    double r2[] = {8, 3};
    double r3[] = {-3, -3};
    double r4[] = {-5, -12};
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
    cr_assert(getflag(), "Flag if false after first call to assignvct");
    assignvct(k, n);
    cr_assert(!getflag(), "Flag is true after second call to assignvct");
    
    int *c = getclusters();
    cr_assert(c[0] == 1);
    cr_assert(c[1] == 0);
    cr_assert(c[2] == 1);
}


Test(testkmeans, testasssignvct4k) {
    /*
    dists:
        R1   R2    R3   R4   R5
    k1  5.2  15.1  0.1  2.1  5.6
    k2  6.7  15.2  3.1  3.6  5.2
    k3  0.3  10.6  2.7  3.2  3.1
    k4  1.6  3.7   11.3 2.5  4.1
    */
    int k = 4;
    int n = 5;
    initclusters(n);
    initdists(k, n);
    double **d = getdists();
    d[0][0] = 5.2;
    d[1][0] = 6.7;
    d[2][0] = 0.3;  //
    d[3][0] = 1.6;
    
    d[0][1] = 15.1;
    d[1][1] = 15.2;
    d[2][1] = 10.6;
    d[3][1] = 3.7;  //
    
    d[0][2] = 0.1;  //
    d[1][2] = 3.1;
    d[2][2] = 2.7;
    d[3][2] = 11.3;

    d[0][3] = 2.1;  //
    d[1][3] = 3.6;
    d[2][3] = 3.2;
    d[3][3] = 2.5;

    d[0][4] = 5.6;
    d[1][4] = 5.2;
    d[2][4] = 3.1;  //
    d[3][4] = 4.1;

    assignvct(k, n);
    cr_assert(getflag(), "Flag is false after first call to assignvct");
    assignvct(k, n);
    cr_assert(!getflag(), "Flag is true after second call to assignvct");

    int *c = getclusters();
    cr_assert(c[0] == 2, "R1 cluster: %d != 2", c[0]);
    cr_assert(c[1] == 3, "R2 cluster: %d != 3", c[1]);
    cr_assert(c[2] == 0, "R3 cluster: %d != 0", c[2]);
    cr_assert(c[3] == 0, "R4 cluster: %d != 0", c[3]);
    cr_assert(c[4] == 2, "R5 cluster: %d != 2", c[4]);
}


Test(testkmeans, test2dclustering2k) {
    int k = 2;
    int n = 4;
    int d = 2;
    Vector *R = malloc(sizeof(*R) * n);
    double r1[] = {3, 3};
    double r2[] = {4, 4};
    double r3[] = {-3, -3};
    double r4[] = {-4, -4};
    R[0] = vector_init_by_array(d, r1);
    R[1] = vector_init_by_array(d, r2);
    R[2] = vector_init_by_array(d, r3);
    R[3] = vector_init_by_array(d, r4);

    clustering(R, k, n, 10);
    int *c = getclusters();
    cr_assert(c[0] == c[1], "R1 cluster: %d != R2 cluster: %d", c[0], c[1]);
    cr_assert(c[0] != c[3], "R1 cluster: %d == R4 cluster: %d", c[0], c[3]);
    cr_assert(c[2] == c[3], "R3 cluster: %d != R4 cluster: %d", c[2], c[3]);
}



Test(testkmeans, test3dclustering2k) {
    int k = 2;
    int n = 4;
    int d = 3;
    Vector *R = malloc(sizeof(*R) * n);
    double r1[] = {3, 3, 3};
    double r2[] = {4, 4, 4};
    double r3[] = {-3, -3, -3};
    double r4[] = {-4, -4, -4};
    R[0] = vector_init_by_array(d, r1);
    R[1] = vector_init_by_array(d, r2);
    R[2] = vector_init_by_array(d, r3);
    R[3] = vector_init_by_array(d, r4);

    clustering(R, k, n, 10);
    int *c = getclusters();
    cr_assert(c[0] == c[1], "R1 cluster: %d != R2 cluster: %d", c[0], c[1]);
    cr_assert(c[0] != c[3], "R1 cluster: %d == R4 cluster: %d", c[0], c[3]);
    cr_assert(c[2] == c[3], "R3 cluster: %d != R4 cluster: %d", c[2], c[3]);
}


Test(testkmeans, test2dclustering4k) {
    int k = 4;
    int n = 8;
    int d = 2;
    Vector *R = malloc(sizeof(*R) * n);
    double r1[] = {3, 3};
    double r2[] = {5, 5};
    double r3[] = {3, -3};
    double r4[] = {5, -5};
    double r5[] = {-3, -3};
    double r6[] = {-5, -5};
    double r7[] = {-3, 3};
    double r8[] = {-5, 5};
    R[0] = vector_init_by_array(d, r1);
    R[1] = vector_init_by_array(d, r2);
    R[2] = vector_init_by_array(d, r3);
    R[3] = vector_init_by_array(d, r4);
    R[4] = vector_init_by_array(d, r5);
    R[5] = vector_init_by_array(d, r6);
    R[6] = vector_init_by_array(d, r7);
    R[7] = vector_init_by_array(d, r8);

    clustering(R, k, n, 10);
    int *c = getclusters();
    cr_assert(c[0] == c[1]);
}