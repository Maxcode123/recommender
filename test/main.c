#include "../src/preprocess/parser/parser.h"
#include "../src/preprocess/matrix.h"
#include "../src/clustering/kmeans.h"


int main(int argc, char **argv) {
    Vector *R = malloc(sizeof(*R) * 5);
    R[0] = vector_init_by_value(10, 2);
    R[1] = vector_init_by_value(10, 5);
    R[2] = vector_init_by_value(10, 9);
    R[3] = vector_init_by_value(10, 25);
    R[4] = vector_init_by_value(10, 2);

    clustering(R, 2, 5);
    int *c = getclusters();
}