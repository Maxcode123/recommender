#include "hashset.h"

typedef struct Entry {
    char *key;
    void *value;
} Entry;

typedef struct HashTable {
    Entry *entries;
    int size;
} HashTable;

/* djb2 hash algorithm */
unsigned long hash_hashset(unsigned char *key) {
    unsigned long hash = 5381;
    int c;
    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % HASH_TABLE_SIZE;
}

void init_hashset(HashTable *table) {
    table->entries = malloc(HASH_TABLE_SIZE * sizeof(Entry));
    table->size = HASH_TABLE_SIZE;
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        table->entries[i].key = NULL;
        table->entries[i].value = 0;
    }
}

void insert_hashtable(HashTable *table, char *key, void *value) {
    unsigned long hash = hash_hashset((unsigned char *) key) % table->size;
    while (table->entries[hash].key != NULL && strcmp(table->entries[hash].key, key) != 0) {
        hash = (hash + 1) % table->size;
    }
    table->entries[hash].key = key;
    table->entries[hash].value = value;
}

void *search_hashtable(HashTable *table, char *key) {
    unsigned long index = hash_hashset((unsigned char *) key);
    while (table->entries[index].key != NULL && strcmp(table->entries[index].key, key) != 0) {
        index = (index + 1) % table->size;
    }
    if (table->entries[index].key != NULL) {
        printf("----------------------------------\n");
        printf("Search --> Key: [%2s]  Found --> Value: [%2s]\n",key,table->entries[index].value);
        printf("----------------------------------\n");
        return table->entries[index].value;
    }
    printf("Key:[%2s] does not exists.\n",key);
    return NULL;
}


void print_hashtable(HashTable *table) {
    for (int i = 0; i < table->size; i++) {
        if (table->entries[i].key != NULL) {
            printf("key: %s, value: %2s\n", table->entries[i].key, (uint8_t *) table->entries[i].value);
        }
    }
}


int delete_hashtable(HashTable *table, char *key) {
    unsigned long index = hash_hashset((unsigned char *) key);
    while (table->entries[index].key != NULL && strcmp(table->entries[index].key, key) != 0) {
        index = (index + 1) % table->size;
    }
    if (table->entries[index].key != NULL) {
        table->entries[index].key = NULL;
        table->entries[index].value = NULL;
        return 1;
    }
    return 0;
}


/* minor tests */
//int main() {
//    HashTable h1;
//    init_hashset(&h1);
//    insert_hashtable(&h1, "kwn",  "Test123");
//    insert_hashtable(&h1, "kwn",  "Not Valid");
//    insert_hashtable(&h1, "kwn",  "Valid");
//    insert_hashtable(&h1, "max", "2500 + 2500");
//    insert_hashtable(&h1, "andreou", "Lets gooo");
//    print_hashtable(&h1);
//    search_hashtable(&h1,"kwn");
//    delete_hashtable(&h1,"kwn");
//    search_hashtable(&h1,"kwn");
//    return 0;
//
//}
