#include "../src/preprocess/parser/parser.h"
#include "../src/preprocess/matrix.h"
#include "../src/clustering/kmeans.h"


int main(int argc, char **argv) {

    int k = 2;
    int n = 4;
    int d = 2;
    Vector *R = malloc(sizeof(*R) * n);
    int r1[] = {3, 3};
    int r2[] = {6, 6};
    int r3[] = {-3, -3};
    int r4[] = {-5, -5};
    R[0] = vector_init_by_array(d, r1);
    R[1] = vector_init_by_array(d, r2);
    R[2] = vector_init_by_array(d, r3);
    R[3] = vector_init_by_array(d, r4);

    clustering(R, k, n);
}