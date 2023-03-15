#pragma once

#include "../utils/vector.h"
#include "../utils/hashset.h"
#include "../utils/list.h"
#include "parser/parser.h"
#include "filter.h"

// Creates data matrix, i.e. an array of vectors.
void matrix(Vector*, HashTable, HashTable);

