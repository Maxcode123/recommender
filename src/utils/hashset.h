#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Entry {
    void *key;
    void *value;
} *Entry;

typedef struct _HashTable {
    struct _Entry *entries;
    int max_size;
    int valid_records; //todo: is it necessary?
} *HashTable;

// djb2 hash algorithm
unsigned long ht_hash(unsigned char *key, int max_size);

//Initialize the ht by suze
HashTable ht_init(int size);

//Insert new record to ht
void ht_insert(HashTable table, char *key, void *value);

//Gets the record by "key"
void *ht_search(HashTable table, char *key);

//Deletes a record of ht.
// Success: 1
// Fail: 0
int ht_delete(HashTable table, char *key);

//Gets the size of the valid records
int ht_size(HashTable table);


