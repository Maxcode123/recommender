#include "hashset.h"

unsigned long ht_hash(unsigned char *key) {
    unsigned long hash = 5381;
    int c;
    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % 50;
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
    unsigned long hash = ht_hash((unsigned char *) key) % table->max_size;
    while (table->entries[hash].key != NULL && strcmp(table->entries[hash].key, key) != 0) {
        hash = (hash + 1) % table->max_size;
    }
    //todo: n(n) problem
//    if(search_hashtable(table,key)){
//        table->valid_records++;
//    }
    table->entries[hash].key = key;
    table->entries[hash].value = value;
}

void *ht_search(HashTable table, char *key) {
    unsigned long index = ht_hash((unsigned char *) key);
    while (table->entries[index].key != NULL && strcmp(table->entries[index].key, key) != 0) {
        index = (index + 1) % table->max_size;
    }
    if (table->entries[index].key != NULL) {
        printf("----------------------------------\n");
        printf("Search --> Key: [%2s]  Found --> Value: [%2s]\n", key, table->entries[index].value);
        printf("----------------------------------\n");
        return table->entries[index].value;
    }
    printf("Key:[%2s] does not exists.\n", key);
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
    unsigned long index = ht_hash((unsigned char *) key);
    while (table->entries[index].key != NULL && strcmp(table->entries[index].key, key) != 0) {
        index = (index + 1) % table->max_size;
    }
    if (table->entries[index].key != NULL) {
        table->entries[index].key = NULL;
        table->entries[index].value = NULL;
        //todo: n(n) problem
//    if(search_hashtable(table,key)){
//        table->valid_records++;
//    }
        return 1;
    }
    return 0;
}


//todo: not working properly yet
int ht_valid_size(HashTable table) {
    return table->valid_records;
}


/* minor tests */
int main() {
    HashTable ht = ht_init(100);
    ht_insert(ht, "kwn", "Test123");
    ht_insert(ht, "kwn", "Not Valid");
    ht_insert(ht, "kwn", "Valid");
    ht_insert(ht, "max", "2500 + 2500");
    ht_insert(ht, "andreou", "Lets gooo");
    ht_print(ht);
    ht_search(ht, "kwn");
//    printf("size of hashmap: %d\n", ht_get_valid_records(ht));
    ht_delete(ht, "kwn");
//    printf("size of hashmap: %d\n", ht_get_valid_records(ht));
    ht_search(ht, "kwn");
    return 0;

}
