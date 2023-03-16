#include "../src/preprocess/parser/parser.h"
#include "../src/preprocess/matrix.h"
#include "../src/clustering/kmeans.h"


int main(int argc, char **argv) {

    int k = 4;
    int n = 8;
    int d = 2;
    Vector *R = malloc(sizeof(*R) * n);
    int r1[] = {3, 3};
    int r2[] = {5, 5};
    int r3[] = {3, -3};
    int r4[] = {5, -5};
    int r5[] = {-3, -3};
    int r6[] = {-5, -5};
    int r7[] = {-3, 3};
    int r8[] = {-5, 5};
    R[0] = vector_init_by_array(d, r1);
    R[1] = vector_init_by_array(d, r2);
    R[2] = vector_init_by_array(d, r3);
    R[3] = vector_init_by_array(d, r4);
    R[4] = vector_init_by_array(d, r5);
    R[5] = vector_init_by_array(d, r6);
    R[6] = vector_init_by_array(d, r7);
    R[7] = vector_init_by_array(d, r8);

    clustering(R, k, n);
}