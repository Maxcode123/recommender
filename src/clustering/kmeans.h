#pragma once

#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

#include "../utils/vector.h"

static Vector *centroids; // Array of centroids
static int *clusters; // Array of cluster numbers, indexed by array of vectors.

// Returns mapping of cluster to array of vectors.
int *getclusters();

// Returns array of centroids.
Vector *getcentroids();

// Allocates memory for cluster array and initializes all values to 0.
void initclusters(int);

// repeat-assignment flag
static bool flag;

/* Matrix of distances of each vector from centroids. Each column represents a
vector, each row represents a centroid. */
static double **dists;

// Returns matrix of distances.
double **getdists();

// Prints distance matrix in nice format
void printdists(int, int);

// Alloactes memory for distance matrix, initializes all values to 0.
void initdists(int, int);

// True if centroids have been initialized, i.e. memory has been allocated.
static bool _initcentroids = false;

// Initializes centroids, chooses k first vectors as initial centroids.
void initcentroids(Vector*, int);

// Performs assignment step. Calculates distances and assigns vectors to clusters.
void assignment(Vector*, int, int);

// Calculates the distance between two vectors.
double calcdistance(Vector, Vector);

/* Assigns each vector to a cluster according to distance matrix, 
makes flag = false if no new assignment is performed. */
void assignvct(int, int);

// Calculates centroids from the vectors of each cluster.
void calccentroids(Vector*, int, int);

/* Applies k-means clustering to given array of vectors. Second argument is the
number of clusters, third argument is the length of the vector array. */ 
void clustering(Vector*, int, int);