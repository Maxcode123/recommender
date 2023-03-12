#pragma once

#include "parser/parser.h"
#include "../utils/list.h"
#include "../utils/hashset.h"

// Bins for number of ratings; used in ratings histogram.
# define N_RATINGS_CLUSTER_1(r) r > 0 && r < 20
# define N_RATINGS_CLUSTER_2(r) r >= 20 && r < 40
# define N_RATINGS_CLUSTER_3(r) r >= 40 && r < 60
# define N_RATINGS_CLUSTER_4(r) r >= 60 && r <= 80
# define N_RATINGS_CLUSTER_5(r) r > 80

/* Bins for days between first and last rating of user; used in dates 
histogram. */
# define N_DAYS_CLUSTER_1(d) d > 0 && d < 365
# define N_DAYS_CLUSTER_2(d) d >= 365 && d < 2 * 365
# define N_DAYS_CLUSTER_3(d) d >= 2 * 365 && d < 3 * 365
# define N_DAYS_CLUSTER_4(d) d >= 3 * 365

/* Parses all files and writes to file data to plot frequency histograms for
number of ratings per user and date interval of ratings per user. */
void main();

// Writes data for number of ratings per user to file with given filename.
void ratingshst(HashTable, char*);

/* Writes data for number of users that made ratings within certain time 
intervals to file with given filename */
void dateshst(Map, char*);