
#ifndef __BASELIB_HASH_TABLE_H
#define __BASELIB_HASH_TABLE_H

#include <stdbool.h>

#include "any.h"


struct HashTable;
typedef struct HashTable HashTable;

HashTable * hash_table_new();

void hash_table_destroy(HashTable * dictionary);
void hash_table_destroy_and_free(HashTable * dictionary);
void hash_table_destroy_and_user_free(HashTable * dictionary, void (*callback)(void *));
void hash_table_destroy_and(HashTable * dictionary, void (*callback)(Any));


List * hash_table_get_keys(HashTable * dictionary);


void hash_table_clear(HashTable * dictionary);
void hash_table_clear_and_free(HashTable * dictionary);
void hash_table_clear_and_user_free(HashTable * dictionary, void (*callback)(void *));
void hash_table_clear_and(HashTable * dictionary, void (*callback)(Any));


bool hash_table_has(HashTable * dictionary, char * key);
Any hash_table_get(HashTable * dictionary, char * key);
bool hash_table_try_get(HashTable * dictionary, char * key, Any * value);

void hash_table_put(HashTable * dictionary, char * key, Any value);
bool hash_table_try_put(HashTable * dictionary, char * key, Any value);


void hash_table_set(HashTable * dictionary, char * key, Any value);
void hash_table_set_and_free(HashTable * dictionary, char * key, Any value);
void hash_table_set_and_user_free(HashTable * dictionary, char * key, Any value, void (*callback)(void *));
void hash_table_set_and(HashTable * dictionary, char * key, Any value, void (*callback)(Any));

Any hash_table_remove(HashTable * dictionary, char * key);

#endif
