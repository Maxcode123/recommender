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

Test(testmatrix, testtovectors) {
    Matrix M = matrix(3, 3);
    double _m0[] = {2.3, 1.1, 5.2};
    double _m1[] = {1.1, 1.2, 0.9};
    double _m2[] = {5.2, 0.9, 4.6};
    M->matrix[0] = _m0;
    M->matrix[1] = _m1;
    M->matrix[2] = _m2;
    Vector *v = tovectors(M);
    cr_assert(vector_get(v[0], 0) == 2.3);
    cr_assert(vector_get(v[0], 1) == 1.1);
    cr_assert(vector_get(v[0], 2) == 5.2);
    cr_assert(vector_get(v[1], 0) == 1.1);
    cr_assert(vector_get(v[1], 1) == 1.2);
    cr_assert(vector_get(v[1], 2) == 0.9);
    cr_assert(vector_get(v[2], 0) == 5.2);
    cr_assert(vector_get(v[2], 1) == 0.9);
    cr_assert(vector_get(v[2], 2) == 4.6);
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

Test(testmatrix, testnew) {
    Matrix M = matrix(3, 3);
   double _m0[] = {2.3, 1.1, 5.2};
   double _m1[] = {1.1, 1.2, 0.9};
   double _m2[] = {5.2, 0.9, 4.6};
   M->matrix[0] = _m0;
   M->matrix[1] = _m1;
   M->matrix[2] = _m2;

   Matrix M2 = matrix_copy(M);
   // mutate M and assert M2 is not changed
   M->matrix[0][0] = 10.2;
   cr_assert(M2->matrix[0][0] == 2.3);
}

// Test(testmatrix, testeigenvals) {
//     /*
//     M
//     2.3 1.1 5.2
//     1.1 1.2 0.9
//     5.2 0.9 4.6

//     λ1 = -1.905
//     λ2 = 0.982
//     λ3 = 9.023
//     */
//    Matrix M = matrix(3, 3);
//    double _m0[] = {2.3, 1.1, 5.2};
//    double _m1[] = {1.1, 1.2, 0.9};
//    double _m2[] = {5.2, 0.9, 4.6};
//    M->matrix[0] = _m0;
//    M->matrix[1] = _m1;
//    M->matrix[2] = _m2;
   
//    Vector *E = malloc(sizeof(*E)*3);
//    E[0] = vector_create(3);
//    E[1] = vector_create(3);
//    E[2] = vector_create(3);
//    eigen(E, M);
//    cr_assert(fabs(M->matrix[0][0] - (-1.905)) < 0.001);
//    cr_assert(fabs(M->matrix[1][1] - 0.982) < 0.001);
//    cr_assert(fabs(M->matrix[2][2] - 9.023) < 0.001);
// }

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
   
//    Matrix _M = matrix_copy(M);   
   
//    double *eigvals = malloc(sizeof(double)*4);
//    Vector *E = malloc(sizeof(*E)*4);
//    E[0] = vector_create(4);
//    E[1] = vector_create(4);
//    E[2] = vector_create(4);
//    E[3] = vector_create(4);
//    eigen(E, M);

//    /*
//    Test that V = _V, where V = M*v1 and _V = λ1*v1, i.e.:
//    M*v1 = λ1*v1 (eigenvalue and eigenvector definition).
//    */
//    Matrix V = matrix(4, 1);
//    Matrix V1 = colvec(E[0]);
   
//    multpl(_M, V1, V, 1, 1);

//    Vector _V = E[0];
//    vector_scale(_V, M->matrix[0][0]);

//    for (int i = 0; i < V->cols; i++) {
//     cr_assert(fabs(V->matrix[i][0] - _V->items[i]) < 0.001, "%f != %f", V->matrix[i][0], _V->items[i]);
//    }
// }