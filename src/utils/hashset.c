#include "hashset.h"

unsigned long ht_hash(unsigned char *key, int max_size) {
    unsigned long hash = 5381;
    int c;
    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % max_size;
}

HashTable ht_init(int size) {
    HashTable hash_table = (HashTable) malloc(sizeof(struct _HashTable));
    hash_table->entries = (Entry) malloc(sizeof(struct _Entry) * size);
    hash_table->max_size = size;
    hash_table->valid_records = 0;

    for (int i = 0; i < size; i++) {
        hash_table->entries[i].key = NULL;
        hash_table->entries[i].value = NULL;
    }

    return hash_table;
}


void ht_insert(HashTable table, char *key, void *value) {
    unsigned long hash = ht_hash((unsigned char *) key, table->max_size);
    while (table->entries[hash].key != NULL && strcmp(table->entries[hash].key, key) != 0) {
        hash = (hash + 1) % table->max_size;
    }
    if (table->entries[hash].key == NULL) table->valid_records++;
    table->entries[hash].key = key;
    table->entries[hash].value = value;
}

void *ht_search(HashTable table, char *key) {
    unsigned long index = ht_hash((unsigned char *) key, table->max_size);
    while (table->entries[index].key != NULL && strcmp(table->entries[index].key, key) != 0) {
        index = (index + 1) % table->max_size;
    }
    if (table->entries[index].key != NULL) {
        return table->entries[index].value;
    }
    return NULL;
}


void ht_print(HashTable table) {
    for (int i = 0; i < table->max_size; i++) {
        if (table->entries[i].key != NULL) {
            printf("key: %s, value: %2s\n", table->entries[i].key, (uint8_t *) table->entries[i].value);
        }
    }
}


int ht_delete(HashTable table, char *key) {
    unsigned long index = ht_hash((unsigned char *) key, table->max_size);
    while (table->entries[index].key != NULL && strcmp(table->entries[index].key, key) != 0) {
        index = (index + 1) % table->max_size;
    }
    if (table->entries[index].key != NULL) {
        table->entries[index].key = NULL;
        table->entries[index].value = NULL;
        table->valid_records--;
        //todo: n(n) problem
//    if(search_hashtable(table,key)){
//        table->valid_records++;
//    }
        return 1;
    }
    return 0;
}


int ht_size(HashTable table) {
    return table->valid_records;
}
