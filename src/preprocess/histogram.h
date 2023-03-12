#pragma once

#include "parser/parser.h"
#include "../utils/list.h"
#include "../utils/hashset.h"


/* Bins for days between first and last rating of user; used in dates 
histogram. */
# define N_DAYS_CLUSTER_1(d) d > 0 && d < 365
# define N_DAYS_CLUSTER_2(d) d >= 365 && d < 2 * 365
# define N_DAYS_CLUSTER_3(d) d >= 2 * 365 && d < 3 * 365
# define N_DAYS_CLUSTER_4(d) d >= 3 * 365


// Rating histogram bin boundaries.
int _c1, _c2, _c3, _c4, _c5;

// Define rating histogram bin boundaries.
void defbins(int, int, int, int, int);

// Returns true if given value is within ratings bin 1.
bool rbin1(int);

// Returns true if given value is within ratings bin 2.
bool rbin2(int);

// Returns true if given value is within ratings bin 3.
bool rbin3(int);

// Returns true if given value is within ratings bin 4.
bool rbin4(int);

// Returns true if given value is within ratings bin 5.
bool rbin5(int);

// Writes data for number of ratings per user to file with given filename.
void ratingshst(HashTable, char*);

/* Writes data for number of users that made ratings within certain time 
intervals to file with given filename */
void dateshst(Map, char*);