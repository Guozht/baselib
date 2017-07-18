

#include "list.h"
#include "list_struct.h"
#include "linked_list.h"
#include "array_list.h"
#include "any.h"

#include <assert.h>
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

void list_set(List * list, unsigned int index, Any element)
{
  assert(list);

  list->list_set(list, index, element);
}

Any list_remove(List * list, unsigned int index)
{
  assert(list);

  return list->list_remove(list, index);
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