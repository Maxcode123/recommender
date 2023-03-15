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

// Allocates memory for cluster array and initializes all values to 0.
void initclusters(int);

// repeat-assignment flag
static bool flag;

/* Matrix of distances of each vector from centroids. Each row represents a
vector, each column represents a centroid. */
static double **dists;

// Alloactes memory for distance matrix, initializes all values to 0.
void initdists(int, int);

// True if centroids have been initialized, i.e. memory has been allocated.
static bool _initcentroids = false;

// Initializes centroids, chooses random vectors as initial centroids.
void initcentroids(Vector*, int, int);

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