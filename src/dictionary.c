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

#include <assert.h>

#include "any.h"
#include "hash_table.h"
#include "mtest.h"
#include "linked_list.h"
#include "list.h"
#include "strings.h"

#include "dictionary.h"
#include "dictionary_struct.h"

Dictionary * dictionary_new(DictionaryType type)
{
  switch (type)
  {

    case DICTIONARY_TYPE_HASH_TABLE:
      return (Dictionary *) hash_table_new();

    default:
      assert(0); /* UNKNOWN TYPE */
  }
}

void dictionary_destroy(Dictionary * dictionary)
{
  assert(dictionary);

  dictionary->dictionary_destroy(dictionary);
}

void dictionary_destroy_and_free(Dictionary * dictionary)
{
  assert(dictionary);

  dictionary->dictionary_destroy_and_free(dictionary);
}

void dictionary_destroy_and_user_free(Dictionary * dictionary, void (*callback)(void *))
{
  assert(dictionary);

  dictionary->dictionary_destroy_and_user_free(dictionary, callback);
}

void dictionary_destroy_and(Dictionary * dictionary, void (*callback)(Any))
{
  assert(dictionary);

  dictionary->dictionary_destroy_and(dictionary, callback);
}


DictionaryType dictionary_get_type(Dictionary * dictionary)
{
  assert(dictionary);

  return dictionary->type;
}

List * dictionary_get_keys(Dictionary * dictionary)
{
  assert(dictionary);

  List * list = (List *) linked_list_new();
  ListTraversal * trav = list_get_traversal(dictionary->keys);

  while (!list_traversal_completed(trav))
  {
    char * value = any_to_str(list_traversal_next(trav));
    list_add(list, str_to_any(strings_clone(value)));
  }

  return list;
}


void dictionary_clear(Dictionary * dictionary)
{
  assert(dictionary);

  dictionary->dictionary_clear(dictionary);
}

void dictionary_clear_and_free(Dictionary * dictionary)
{
  assert(dictionary);

  dictionary->dictionary_clear_and_free(dictionary);
}

void dictionary_clear_and_user_free(Dictionary * dictionary, void (*callback)(void *))
{
  assert(dictionary);

  dictionary->dictionary_clear_and_user_free(dictionary, callback);
}

void dictionary_clear_and(Dictionary * dictionary, void (*callback)(Any))
{
  assert(dictionary);

  dictionary->dictionary_clear_and(dictionary, callback);
}


bool dictionary_has(Dictionary * dictionary, char * key)
{
  assert(dictionary);

  return dictionary->dictionary_has(dictionary, key);
}

Any dictionary_get(Dictionary * dictionary, char * key)
{
  assert(dictionary);

  return dictionary->dictionary_get(dictionary, key);
}

bool dictionary_try_get(Dictionary * dictionary, char * key, Any * value)
{
  assert(dictionary);

  return dictionary->dictionary_try_get(dictionary, key, value);
}

void dictionary_put(Dictionary * dictionary, char * key, Any value)
{
  assert(dictionary);

  dictionary->dictionary_put(dictionary, key, value);
}

bool dictionary_try_put(Dictionary * dictionary, char * key, Any value)
{
  assert(dictionary);

  return dictionary->dictionary_try_put(dictionary, key, value);
}


void dictionary_set(Dictionary * dictionary, char * key, Any value)
{
  assert(dictionary);

  dictionary->dictionary_set(dictionary, key, value);
}

void dictionary_set_and_free(Dictionary * dictionary, char * key, Any value)
{
  assert(dictionary);

  dictionary->dictionary_set_and_free(dictionary, key, value);
}
void dictionary_set_and_user_free(Dictionary * dictionary, char * key, Any value, void (*callback)(void *))
{
  assert(dictionary);

  dictionary->dictionary_set_and_user_free(dictionary, key, value, callback);
}
void dictionary_set_and(Dictionary * dictionary, char * key, Any value, void (*callback)(Any))
{
  assert(dictionary);

  dictionary->dictionary_set_and(dictionary, key, value, callback);
}

Any dictionary_remove(Dictionary * dictionary, char * key)
{
  assert(dictionary);

  return dictionary->dictionary_remove(dictionary, key);
}
