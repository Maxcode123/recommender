#pragma once

#include "list.h"

typedef ListItem MapItem;

typedef struct _Map {
    List lst;
} *Map;

// Initializes a map.
Map map();

// Associates key with MapItem, if key already exists returns False, else True.
bool map_put(Map, key, MapItem);

// Returns MapItem associated with key. If there is no such item, returns NULL.
MapItem map_get(Map, key);

// Returns the number of items in map.
int map_len(Map);

// Clears all items from map.
void map_clear(Map);