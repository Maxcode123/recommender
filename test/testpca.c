#include <criterion/criterion.h>

#include "../src/clustering/PCA.h"


Test(testpca, testsort) {
    double arr[] = {2.9, 10.5, 1.2, 0.1, 9.2};
    qsort(arr, 5, sizeof(double), compare);
    cr_assert(arr[0] == 10.5, "%f != %f", arr[0], 10.5);
    cr_assert(arr[1] == 9.2);
    cr_assert(arr[2] == 2.9);
    cr_assert(arr[3] == 1.2);
    cr_assert(arr[4] == 0.1);
}

Test(testpca, testindeces) {
    double arr[] = {0.18, 19.2, 3.2, 4.5, 1.8};
    int ind[] = {0, 0, 0};
    indeces(arr, 5, ind, 3);
    cr_assert(ind[0] == 1);
    cr_assert(ind[1] == 3);
    cr_assert(ind[2] == 2);
}

Test(testpca, testreduce) {
    Matrix m = matrix(4, 3);
    double _m0[] = {1, 2, 3};
    double _m1[] = {1, 2, 3};
    double _m2[] = {1, 2, 3};
    double _m3[] = {1, 2, 3};
    m->matrix[0] = _m0;
    m->matrix[1] = _m1;
    m->matrix[2] = _m2;
    m->matrix[3] = _m3;

    int ind[] = {0, 2};
    Matrix m2 = reduce(m, ind, 2);
    cr_assert(m2->matrix[0][0] == 1);
    cr_assert(m2->matrix[3][0] == 1);
    
    cr_assert(m2->matrix[0][1] == 3);
    cr_assert(m2->matrix[3][1] == 3);
}

Test(testpca, testPCA) {
    Matrix m = matrix(4, 3);
    double _m0[] = {1, 2, 3};
    double _m1[] = {1, 2, 3};
    double _m2[] = {1, 2, 3};
    double _m3[] = {1, 2, 3};
    m->matrix[0] = _m0;
    m->matrix[1] = _m1;
    m->matrix[2] = _m2;
    m->matrix[3] = _m3;
    
    PCA(&m, 2);
    cr_assert(m->rows == 4, "%d != %d", m->rows, 4);
    cr_assert(m->cols == 2);
}