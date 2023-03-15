#include "../src/preprocess/parser/parser.h"
#include "../src/preprocess/matrix.h"
#include "../src/clustering/kmeans.h"


int main(int argc, char **argv) {

    int k = 2;
    int n = 4;
    int d = 2;

    Vector *R = malloc(sizeof(*R) * n);
    int r1[] = {2, 7};
    int r2[] = {8, 3};
    int r3[] = {-3, -3};
    int r4[] = {-4, -4};
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
}