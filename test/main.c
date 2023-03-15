#include "../src/preprocess/parser/parser.h"
#include "../src/preprocess/matrix.h"
#include "../src/clustering/kmeans.h"


int main(int argc, char **argv) {


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
}