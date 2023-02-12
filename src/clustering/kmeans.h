#pragma once

#include "../utils/vector.h"
#include "../utils/map.h"

static Vector *centroids; // Array of centroids
static Map clusters; // Mapping of cluster to array of vectors.

// Returns mapping of cluster to array of vectors.
Map getclusters();

// repeat-assignment flag
static bool flag;

/* Matrix of distances of each vector from centroids. Each row represents a
vector, each column represents a centroid. */
static double **dists;

// Initializes centroids, chooses random vectors as initial centroids.
void initcentroids(Vector*);

// Calculates the distance between two vectors.
double calcdistance(Vector, Vector);

/* Assigns each vector to a cluster according to distance matrix, 
makes flag = false if no new assignment is performed. */
void assignvct();

// Calculates centroids from the vectors of each cluster.
void calccentroids();

/* Applies k-means clustering to given array of vectors. Second argument is the
number of clusters, third argument is the length of the vector array. */ 
void clustering(Vector*, int, int);