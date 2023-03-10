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

// Date histogram bin boundaries
int _d1, _d2, _d3, _d4;

// Define date histogram bin boundaries.
void defdbins(int, int, int, int);

// Returns true if given value is within date bins 1.
bool dbin1(int);

// Returns true if given value is within date bins 2.
bool dbin2(int);

// Returns true if given value is within date bins 3.
bool dbin3(int);

// Returns true if given value is within date bins 4.
bool dbin4(int);

// Returns true if given value is within date bins 5.
bool dbin5(int);

// Rating histogram bin boundaries.
int _c1, _c2, _c3, _c4, _c5;

// Define rating histogram bin boundaries.
void defrbins(int, int, int, int, int);

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
void dateshst(HashTable, char*);