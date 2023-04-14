#pragma once

#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

#include "../utils/vector.h"
#include "../utils/hashset.h"

static Vector *centroids; // Array of centroids
static int *clusters; // Array of cluster numbers, indexed by array of vectors.

// Returns array of cluster numbers, indexed by array of vectors.
int *getclusters();

// Returns array of centroids.
Vector *getcentroids();

/* Allocates memory for cluster array and initializes all values to 0. Receives
as input the total number of records n, NOT THE NUMBER OF CLUSTERS k. */
void initclusters(int);

/* repeat-assignment flag; while this flag is true the kmeans algorithm calculates
centroids and assigns vectors to clusters. */
static bool flag;

// Returns repeat-assignment flag
bool getflag();

/* Matrix of distances of each vector from centroids. Each column represents a
vector, each row represents a centroid. 
e.g. 3 clusters 4 2-dimensional vectors
     R1   R2   R3   R4
    -------------------
k1 | r11  r12  r13  r14
k2 | r21  r22  r23  r24
k3 | r31  r32  r33  r34

rij is the distance of Rj from ki's centroid.
*/
static double **dists;

// Returns matrix of distances.
double **getdists();

// Prints distance matrix in nice format
void printdists(int, int);

// Allocates memory for distance matrix, initializes all values to 0.
void initdists(int, int);

// True if centroids have been initialized, i.e. memory has been allocated.
static bool _initcentroids = false;

// Initializes centroids, chooses k first vectors as initial centroids.
void initcentroids(Vector*, int, double (*calcd)(Vector, Vector));

// Performs assignment step. Calculates distances and assigns vectors to clusters.
void assignment(Vector*, int, int, double (*calcd)(Vector, Vector));

// Calculates the Euclidean distance between two vectors.
double calcd_euc(Vector, Vector);

// Calculates the cosine distance between two vectors.
double calcd_cos(Vector, Vector);

/* Calculates the distance between two vectors as the percentage of common 
movies rated. */
double calcd_perc(Vector, Vector);

/* Assigns each vector to a cluster according to distance matrix, 
makes flag = false if no new assignment is performed. */
void assignvct(int, int);

// Calculates centroids from the vectors of each cluster.
void calccentroids(Vector*, int, int);

/* Applies k-means clustering to given array of vectors. Second argument is the
number of clusters, third argument is the length of the vector array and fourth
argument is the maximum iterations. */ 
void clustering(Vector*, int, int, int, double (*calcd)(Vector, Vector));
