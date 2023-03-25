#include <criterion/criterion.h>

#include "../src/utils/matrix.h"


Test(testmatrix, testinit) {
    Matrix m = matrix(3, 3);
    cr_assert(m->rows == 3);
    cr_assert(m->cols == 3);
}

Test(testmatrix, testinitvalue) {
    Matrix m = matrix(5, 5);
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            cr_assert(m->matrix[i][j] == 0);
        }
    }
}

Test(testmatrix, testassign) {
    Matrix m = matrix(3, 4);
    double m0[] = {0.2, -10.5, 9.2, 4.3};
    m->matrix[0] = m0;
    cr_assert(m->matrix[0][0] == 0.2, "%f != %f", m->matrix[0][0], 0.2);
    cr_assert(m->matrix[0][3] == 4.3, "%f != %f", m->matrix[0][3], 4.3);
}

Test(testmatrix, testtranspose) {
    /*
    m
    0.1 0.2
    0.3 0.4
    
    t (transpose of m)
    0.1 0.3
    0.2 0.4
    */
    Matrix m = matrix(2, 2);
    double _m0[] = {0.1, 0.2};
    double _m1[] = {0.3, 0.4};
    m->matrix[0] = _m0;
    m->matrix[1] = _m1;
    Matrix t = matrix(2, 2);
    transpose(m, t);
    cr_assert(t->matrix[0][0] == 0.1);
    cr_assert(t->matrix[0][1] == 0.3);
    cr_assert(t->matrix[1][0] == 0.2);
    cr_assert(t->matrix[1][1] == 0.4);
}

Test(testmatrix, testtranspose2) {
    /*
    m
    -1.1 4.2 8.2 9.1
    0.3  0.2 3.3 8.1

    t
    -1.1 0.3
    4.2  0.2
    8.2  3.3
    9.1  8.1
    */
   Matrix m = matrix(2, 4);
   double _m0[] = {-1.1, 4.2, 8.2, 9.1};
   double _m1[] = {0.3, 0.2, 3.3, 8.1};
   m->matrix[0] = _m0;
   m->matrix[1] = _m1;
   Matrix t = matrix(4, 2);
   transpose(m, t);
   cr_assert(t->matrix[0][1] == 0.3);
   cr_assert(t->matrix[1][0] == 4.2);
   cr_assert(t->matrix[1][1] == 0.2);
   cr_assert(t->matrix[2][0] == 8.2);
   cr_assert(t->matrix[2][1] == 3.3);
   cr_assert(t->matrix[3][0] == 9.1);
   cr_assert(t->matrix[3][1] == 8.1);
}

Test(testmatrix, testmultpl) {
    /*
    A (2x3)  B (3x2)  C (2x2)
    2 3 4    3 5      17 25
    0 1 2    1 1      5  7
             2 3
    */
   Matrix A = matrix(2, 3);
   double a0[] = {2, 3, 4};
   double a1[] = {0, 1, 2};
    A->matrix[0] = a0;
    A->matrix[1] = a1;

   Matrix B = matrix(3, 2);
   double b0[] = {3, 5};
   double b1[] = {1, 1};
   double b2[] = {2, 3};
   B->matrix[0] = b0;
   B->matrix[1] = b1;
   B->matrix[2] = b2;

   Matrix C = matrix(2, 2);
   multpl(A, B, C, 1, 1);
   cr_assert(C->matrix[0][0] == 17);
   cr_assert(C->matrix[0][1] == 25);
   cr_assert(C->matrix[1][0] == 5);
   cr_assert(C->matrix[1][1] == 7);
}

Test(testmatrix, testmultplzero) {
    Matrix A = matrix(50, 108);
    Matrix B = matrix(108, 124);
    Matrix C = matrix(50, 124);
    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 124; j++) {
            C->matrix[i][j] = 1;
        }
    }
    multpl(A, B, C, 2, 27);
    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 124; j++) {
            cr_assert(C->matrix[i][j] == 0);
        }
    }
}

Test(testmatrix, testfromvectors) {
    Vector *R = malloc(sizeof(*R)*3);
    R[0] = vector_init_by_value(2, 1);
    R[1] = vector_init_by_value(2, 5);
    R[2] = vector_init_by_value(2, -2);
    Matrix m = fromvectors(R, 3);
    cr_assert(m->rows == 3);
    cr_assert(m->cols == 2);
    cr_assert(m->matrix[0][0] == 1);
    cr_assert(m->matrix[0][1] == 1);
    cr_assert(m->matrix[1][0] == 5);
    cr_assert(m->matrix[1][1] == 5);
    cr_assert(m->matrix[2][0] == -2);
    cr_assert(m->matrix[2][1] == -2);
}

Test(testmatrix, testrowvec) {
    Vector R = vector_init_by_value(3, 3.14);
    Matrix m = rowvec(R);
    cr_assert(m->matrix[0][0] == 3.14);
    cr_assert(m->matrix[0][1] == 3.14);
    cr_assert(m->matrix[0][2] == 3.14);
}

Test(testmatrix, testcolvec) {
    Vector R = vector_init_by_value(3, 6.17);
    Matrix m = colvec(R);
    cr_assert(m->matrix[0][0] == 6.17);
    cr_assert(m->matrix[1][0] == 6.17);
    cr_assert(m->matrix[2][0] == 6.17);
}

Test(testmatrix, testeigenvals) {
    /*
    M
    2.3 1.1 5.2
    1.1 1.2 0.9
    5.2 0.9 4.6

    λ1 = -1.905
    λ2 = 0.982
    λ3 = 9.023
    */
   Matrix M = matrix(3, 3);
   double _m0[] = {2.3, 1.1, 5.2};
   double _m1[] = {1.1, 1.2, 0.9};
   double _m2[] = {5.2, 0.9, 4.6};
   M->matrix[0] = _m0;
   M->matrix[1] = _m1;
   M->matrix[2] = _m2;
   
   double *eigvals = malloc(sizeof(double)*3);
   Vector *E = malloc(sizeof(*E)*3);
   eigen(eigvals, E, M);
   cr_assert(fabs(eigvals[0] - (-1.905)) < 0.001, "%f != %f", eigvals[0], -1.905);
   cr_assert(fabs(eigvals[1] - 0.982) < 0.001);
   cr_assert(fabs(eigvals[2] - 9.023) < 0.001);
}

// Test(testmatrix, testeigenvectors) {
//    /*
//    M
//    2.3 2.1 5.2 9.8
//    2.1 1.2 0.9 5.5
//    5.2 0.9 4.6 5.9
//    9.8 5.5 5.9 7.1
//    */
//    Matrix M = matrix(4, 4);
//    double _m0[] = {2.3, 2.1, 5.2, 9.8};
//    double _m1[] = {2.1, 1.2, 0.9, 5.5};
//    double _m2[] = {5.2, 0.9, 4.6, 5.9};
//    double _m3[] = {9.8, 5.5, 5.9, 7.1};
//    M->matrix[0] = _m0;
//    M->matrix[1] = _m1;
//    M->matrix[2] = _m2;
//    M->matrix[3] = _m3;
   
//    double *eigvals = malloc(sizeof(double)*4);
//    Vector *E = malloc(sizeof(*E)*4);
//    eigen(eigvals, E, M);
// }