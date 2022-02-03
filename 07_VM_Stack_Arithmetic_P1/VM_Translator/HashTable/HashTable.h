//
// Created by Toor on 11/8/2021.
//

#ifndef UNTITLED_HASHTABLE_H
#define UNTITLED_HASHTABLE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char *ht_key_t;
typedef void *ht_value_t;

// key => value plus pointer to next item for hash collisions
typedef struct HashTableItem HashTableItem;
struct HashTableItem {
    ht_key_t key;
    ht_value_t value;
    HashTableItem *next;
};

// Contains an array of pointers to HashTableItems
typedef struct HashTable {
    HashTableItem **items;
    size_t size;
    size_t count; // could be used for rehashing in future
} HashTable;

HashTableItem *ht_create_item(ht_key_t key, ht_value_t value);

HashTable *ht_create(size_t size);

void ht_free_item(HashTableItem *item);

void ht_free(HashTable *table);

size_t hash_function(HashTable *table, const char *str);

void ht_insert(HashTable *table, ht_key_t key, ht_value_t value);

void ht_delete(HashTable *table, ht_key_t key);

HashTableItem *ht_search(HashTable *table, ht_key_t key);

void ht_print(HashTable *table);

void ht_print_search(HashTable *table, ht_key_t key);


#endif //UNTITLED_HASHTABLE_H
