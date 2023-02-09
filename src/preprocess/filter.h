#pragma once

#include "parser/parser.h"
#include "../utils/map.h"


# define RMIN 10
# define RMAX 200

/* Filters 1st map based on minimum and maximum allowed number of ratings per
user. */
void filter(Map);

