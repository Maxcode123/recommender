#pragma once

#include "../utils/list.h"
#include "../utils/hashset.h"


# define RMIN 5
# define RMAX 50

/* Filters 1st map based on minimum and maximum allowed number of ratings per
user. */
void filter(HashTable);

