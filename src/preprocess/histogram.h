#pragma once

#include "parser/parser.h"
#include "../utils/list.h"

// Clusters for number of ratings; used in ratings histogram.
# define N_RATINGS_CLUSTER_1(r) r > 0 && r < 50
# define N_RATINGS_CLUSTER_2(r) r >= 50 && r < 100
# define N_RATINGS_CLUSTER_3(r) r >= 100 && r < 150
# define N_RATINGS_CLUSTER_4(r) r >= 150 && r <= 200
# define N_RATINGS_CLUSTER_5(r) r > 200

/* Parses all files and writes to file data to plot frequency histograms for
number of ratings per user and date interval of ratings per user. */
void main();

// Writes data for number of ratings per user to file with given filename.
void ratingshst(Map, char*);

/* Writes data for number of users that made ratings within certain time 
intervals to file with given filename */
void dateshst(Map, char*);