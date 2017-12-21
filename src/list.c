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



#include "list.h"
#include "list_struct.h"
#include "linked_list.h"
#include "array_list.h"
#include "any.h"

#include <assert.h>

List * list_new(ListType type)
{
  switch (type)
  {

    case LIST_TYPE_LINKED_LIST:
      return (List *) linked_list_new();

    case LIST_TYPE_ARRAY_LIST:
      return (List *) array_list_new();

    default:
      assert(0); /* INVALID LIST TYPE */

  }
}


void list_destroy(List * list)
{
  assert(list);

  list->list_destroy(list);
}

void list_destroy_and_free(List * list)
{
  assert(list);

  list->list_destroy_and_free(list);
}

void list_destroy_and_user_free(List * list, void (*callback)(void *))
{
  assert(list);

  list->list_destroy_and_user_free(list, callback);
}

void list_destroy_and(List * list, void (*function)(Any))
{
  assert(list);

  list->list_destroy_and(list, function);
}



unsigned int list_size(List * list)
{
  assert(list);

  return list->list_size(list);
}


bool list_has_open_traversals(List * list)
{
  assert(list);

  sem_wait(&list->mutex);

  bool ret = list->open_traversals > 0;

  sem_post(&list->mutex);

  return ret;
}


bool list_contains(List * list, Any any)
{
  assert(list);

  return list->list_contains(list, any);
}


Any list_get(List * list, unsigned int index)
{
  assert(list);

  return list->list_get(list, index);
}

void list_add(List * list, Any element)
{
  assert(list);

  list->list_add(list, element);
}

void list_add_range(List * list, List * range)
{
  assert(list);

  list->list_add_range(list, range);
}

void list_set(List * list, unsigned int index, Any element)
{
  assert(list);

  list->list_set(list, index, element);
}

Any list_remove_at(List * list, unsigned int index)
{
  assert(list);

  return list->list_remove_at(list, index);
}

unsigned int list_remove(List * list, Any any)
{
  assert(list);

  return list->list_remove(list, any);
}

unsigned int list_remove_and_free(List * list, Any any)
{
  assert(list);

  return list->list_remove_and_free(list, any);
}


void list_clear(List * list)
{
  assert(list);

  return list->list_clear(list);
}

void list_clear_and_free(List * list)
{
  assert(list);

  return list->list_clear_and_free(list);
}

void list_clear_and(List * list, void (*function)(Any))
{
  assert(list);
  assert(function);

  return list->list_clear_and(list, function);
}

Any * list_to_array(List * list)
{
  assert(list);

  return list->list_to_array(list);
}

List * list_sub_list(List * list, unsigned int start, unsigned int end)
{
  assert(list);

  return list->list_sub_list(list, start, end);
}

List * list_clone(List * list)
{
  assert(list);

  return list->list_clone(list);
}


char * list_to_string(List * list)
{
  assert(list);

  return list->list_to_string(list);
}


void list_foreach(List * list, void (*function)(Any any))
{
  assert(list);
  assert(function);

  return list->list_foreach(list, function);
}



ListTraversal * list_get_traversal(List * list)
{
  assert(list);

  return list->list_get_traversal(list);
}

void list_traversal_destroy(ListTraversal * list_traversal)
{
  assert(list_traversal);

  list_traversal->list_traversal_destroy(list_traversal);
}

Any list_traversal_next(ListTraversal * list_traversal)
{
  assert(list_traversal);

  return list_traversal->list_traversal_next(list_traversal);
}
bool list_traversal_completed(ListTraversal * list_traversal)
{
  assert(list_traversal);

  return list_traversal->list_traversal_completed(list_traversal);
}
