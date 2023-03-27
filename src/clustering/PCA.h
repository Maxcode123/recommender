#pragma once

#include "../utils/matrix.h"


// Performs PCA to the given matrix, reduces to given dimensions.
void PCA(Matrix*, int);

// Compares two integers, returns 1 if second is larger than the first.
int compare(const void*, const void*);

/* Returns a new reduced matrix. Second argument is the indeces of the columns
to keep, third argument is the number of columns to keep.*/
Matrix reduce(Matrix, int*, int);

/* Returns the indeces of the n largest elements in the first argument. Second
argument is size of given array. Result is put in third argument.*/
void indeces(double*, int, int*, int n);