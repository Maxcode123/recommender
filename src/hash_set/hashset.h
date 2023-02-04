#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint-gcc.h>

#define HASH_TABLE_SIZE 5

typedef struct Entry Entry;

typedef struct HashTable HashTable;

extern unsigned long hash_hashset(unsigned char *key);

extern void init_hashset(HashTable *table);

extern void insert_hashtable(HashTable *table, char *key, void *value);

extern void *search_hashtable(HashTable *table, char *key);

extern void print_hashtable(HashTable *table);

extern int delete_hashtable(HashTable *table, char *key);

