#include "../src/preprocess/parser/parser.h"
#include "../src/preprocess/filter.h"
#include "../src/clustering/kmeans.h"
#include "../src/preprocess/vectorization.h"
#include "../src/utils/matrix.h"


int main(int argc, char **argv) {
//    M
//    2.3 2.1 5.2 9.8
//    2.1 1.2 0.9 5.5
//    5.2 0.9 4.6 5.9
//    9.8 5.5 5.9 7.1
//    */
   Matrix M = matrix(4, 4);
   double _m0[] = {2.3, 2.1, 5.2, 9.8};
   double _m1[] = {2.1, 1.2, 0.9, 5.5};
   double _m2[] = {5.2, 0.9, 4.6, 5.9};
   double _m3[] = {9.8, 5.5, 5.9, 7.1};
   M->matrix[0] = _m0;
   M->matrix[1] = _m1;
   M->matrix[2] = _m2;
   M->matrix[3] = _m3;
   
   double *eigvals = malloc(sizeof(double)*4);
   Vector *E = malloc(sizeof(*E)*4);
   E[0] = vector_create(4);
   E[1] = vector_create(4);
   E[2] = vector_create(4);
   E[3] = vector_create(4);
   eigen(eigvals, E, M);

   /*
   Test that V = _V, where V = M*v1 and _V = λ1*v1, i.e.:
   M*v1 = λ1*v1 (eigenvalue and eigenvector definition).
   */
   Matrix V = matrix(4, 1);
   multpl(M, colvec(E[0]), V, 1, 1);
   
   Vector v1 = E[0];
   vector_scale(v1, eigvals[0]);

}
