#pragma once

#include "../utils/list.h"
#include "../utils/hashset.h"


# define RMIN 5
# define RMAX 50

/* Filters map based on minimum and maximum allowed number of ratings per
user. Returns list with filtered records.*/
List filter(HashTable, List);

