#pragma once

#include "../utils/matrix.h"
#include "../utils/hashset.h"

/*Creates a hash table with cluster as key and array of vectors as value. 
Second argument is number of clusters. Third argument is length of global
vector array.
*/
HashTable vectormap(Vector*, int k, int n);

// Array of cluster sizes.
int *clustersize;

// Inserts a string to be used as cluster key in vectormap.
void clusterkey(int, char*);

// Creates distance matrix of vector array based on given distance function.
Matrix distmatrix(Vector *, double (*calcd)(Vector, Vector));

/* Returns an array of the k nearest neighbors of the given vector, based on
the given distance matrix. */
Vector *nearest(Vector *, Vector, int k, Matrix dist);
