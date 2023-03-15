#include <criterion/criterion.h>

#include "../../src/clustering/kmeans.h"


Test(testkmeans, test) {
    Vector *R = malloc(sizeof(*R) * 5);
    R[0] = vector_init_by_value(10, 2);
    R[1] = vector_init_by_value(10, 5);
    R[2] = vector_init_by_value(10, 9);
    R[3] = vector_init_by_value(10, 25);
    R[4] = vector_init_by_value(10, 2);

    clustering(R, 2, 5);
    int *c = getclusters();
    cr_assert(c[0] == c[4], "R0 cluster: %d, R4 cluster: %d", c[0], c[4]);
    cr_assert(c[0] != c[3], "R0 cluster: %d, R3 cluster: %d", c[0], c[3]);
}
