#include "../src/preprocess/parser/parser.h"
#include "../src/preprocess/filter.h"
#include "../src/clustering/kmeans.h"
#include "../src/clustering/PCA.h"
#include "../src/preprocess/vectorization.h"
#include "../src/utils/matrix.h"
#include "../src/neuron/neuron.h"
#include "../src/neuron/train.h"


int main(int argc, char **argv) {
    int k = 2;
    int n = 6;
    int d = 4;
    Vector *R = malloc(sizeof(*R) * n);
    double r1[] = {0, 0, 5, 9};
    double r2[] = {0, 0, 2, 5};
    double r3[] = {0, 0, 9, 9};
    double r4[] = {5, 4, 0, 0};
    double r5[] = {1, 1, 0, 0};
    double r6[] = {5, 1, 0, 0};
    R[0] = vector_init_by_array(d, r1);
    R[1] = vector_init_by_array(d, r2);
    R[2] = vector_init_by_array(d, r3);
    R[3] = vector_init_by_array(d, r4);
    R[4] = vector_init_by_array(d, r5);
    R[5] = vector_init_by_array(d, r6);

    clustering(R, k, n, 100, &calcd_perc);
}
