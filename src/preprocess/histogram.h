#pragma once

#include "parser/parser.h"
#include "../utils/list.h"

/* Parses all files and writes to file data to plot frequency histograms for
number of ratings per user and date interval of ratings per user. */
void main();

// Creates data for number of ratings per user histogram.
void ratings(Map);