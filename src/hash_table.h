/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                         *
 *  baselib: a library implementing several simple utilities for C         *
 *  Copyright (C) 2017  LeqxLeqx                                           *
 *                                                                         *
 *  This program is free software: you can redistribute it and/or modify   *
 *  it under the terms of the GNU General Public License as published by   *
 *  the Free Software Foundation, either version 3 of the License, or      *
 *  (at your option) any later version.                                    *
 *                                                                         *
 *  This program is distributed in the hope that it will be useful,        *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *  GNU General Public License for more details.                           *
 *                                                                         *
 *  You should have received a copy of the GNU General Public License      *
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.  *
 *                                                                         *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


#ifndef __BASELIB_HASH_TABLE_H
#define __BASELIB_HASH_TABLE_H

#include <stdbool.h>

#include "any.h"
#include "list.h"


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
