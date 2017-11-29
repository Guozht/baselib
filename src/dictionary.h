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

#ifndef __BASELIB_DICTIONARY_H
#define __BASELIB_DICTIONARY_H

#include <stdbool.h>

#include "any.h"
#include "dictionary_type.h"
#include "list.h"

struct Dictionary;
typedef struct Dictionary Dictionary;

Dictionary * dictionary_new(DictionaryType type);

void dictionary_destroy(Dictionary * dictionary);
void dictionary_destroy_and_free(Dictionary * dictionary);
void dictionary_destroy_and_user_free(Dictionary * dictionary, void (*callback)(void *));
void dictionary_destroy_and(Dictionary * dictionary, void (*callback)(Any));


DictionaryType dictionary_get_type(Dictionary * dictionary);
List * dictionary_get_keys(Dictionary * dictionary);


void dictionary_clear(Dictionary * dictionary);
void dictionary_clear_and_free(Dictionary * dictionary);
void dictionary_clear_and_user_free(Dictionary * dictionary, void (*callback)(void *));
void dictionary_clear_and(Dictionary * dictionary, void (*callback)(Any));


bool dictionary_has(Dictionary * dictionary, char * key);
Any dictionary_get(Dictionary * dictionary, char * key);
bool dictionary_try_get(Dictionary * dictionary, char * key, Any * value);

/*
 * Distinction between put and set is that 
 * put will fail if the key already exists
 */
void dictionary_put(Dictionary * dictionary, char * key, Any value);
bool dictionary_try_put(Dictionary * dictionary, char * key, Any value);


void dictionary_set(Dictionary * dictionary, char * key, Any value);
/*
 * operates on the existing value if one exists
 */
void dictionary_set_and_free(Dictionary * dictionary, char * key, Any value);
void dictionary_set_and_user_free(Dictionary * dictionary, char * key, Any value, void (*callback)(void *));
void dictionary_set_and(Dictionary * dictionary, char * key, Any value, void (*callback)(Any));

Any dictionary_remove(Dictionary * dictionary, char * key);



#endif
