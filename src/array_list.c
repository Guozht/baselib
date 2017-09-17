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


#include "array_list.h"
#include "list.h"
#include "list_struct.h"
#include "list_type.h"
#include "any.h"
#include "string_builder.h"
#include "strings.h"

#include <assert.h>
#include <semaphore.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>



#define ARRAY_LIST_MINIMUM_SIZE 0x10

struct ArrayList
{
  List base;
  Any * array;
  unsigned int size;
  unsigned int array_size;
};

struct ArrayListTraversal
{
  ListTraversal base;
  unsigned int position;
};



/* INTERNAL METHODS */


static void array_list_resize(ArrayList * array_list, unsigned int requested_size)
{

  unsigned int new_size = array_list->array_size;

  if (requested_size >= new_size)
  {
    while (new_size < requested_size)
      new_size *= 2;
  }
  else if (2 * requested_size < new_size)
    new_size = new_size / 2;


  if (new_size < ARRAY_LIST_MINIMUM_SIZE)
    new_size = ARRAY_LIST_MINIMUM_SIZE;


  if (new_size != array_list->array_size)
  {
    array_list->array = (Any *) realloc(array_list->array, sizeof(Any) * new_size);

    assert(array_list->array);
    array_list->array_size = new_size;
  }

}



/* END OF INTERNAL METHODS */



/* methods for ArrayList */

ArrayList * array_list_new()
{

  ArrayList * ret = (ArrayList *) malloc(sizeof(ArrayList));
  assert(ret);

  ret->base.type = LIST_TYPE_ARRAY_LIST;
  ret->base.open_traversals = 0;

  ret->base.list_destroy = (void (*)(List *)) array_list_destroy;
  ret->base.list_destroy_and_free = (void (*)(List *)) array_list_destroy_and_free;
  ret->base.list_destroy_and = (void (*)(List *, void (*)(Any))) array_list_destroy_and;
  ret->base.list_size = (unsigned int (*)(List *)) array_list_size;
  ret->base.list_get = (Any (*)(List *, unsigned int)) array_list_get;
  ret->base.list_add = (void (*)(List *, Any)) array_list_add;
  ret->base.list_add_range = (void (*)(List *, List *)) array_list_add_range;
  ret->base.list_set = (void (*)(List *, unsigned int, Any)) array_list_set;
  ret->base.list_remove_at = (Any (*)(List *, unsigned int)) array_list_remove_at;
  ret->base.list_clear = (void (*)(List *)) array_list_clear;
  ret->base.list_to_array = (Any * (*)(List *)) array_list_to_array;
  ret->base.list_sub_list = (List * (*)(List *, unsigned int, unsigned int)) array_list_sub_list;
  ret->base.list_clone = (List * (*)(List *)) array_list_clone;
  ret->base.list_to_string = (char * (*)(List *)) array_list_to_string;
  ret->base.list_get_traversal = (ListTraversal * (*)(List *)) array_list_get_traversal;

  sem_init(&ret->base.mutex, 0, 1);

  ret->array = (Any *) malloc(sizeof(Any) * ARRAY_LIST_MINIMUM_SIZE);
  assert(ret->array);
  ret->size = 0;
  ret->array_size = ARRAY_LIST_MINIMUM_SIZE;

  return ret;
}
void array_list_destroy(ArrayList * array_list)
{
  assert(array_list);
  assert(array_list->base.open_traversals == 0);

  sem_destroy(&array_list->base.mutex);

  free(array_list->array);
  free(array_list);
}
void array_list_destroy_and_free(ArrayList * array_list)
{
  assert(array_list);
  assert(array_list->base.open_traversals == 0);

  for (unsigned int k = 0; k < array_list->size; k++)
  {
    free(any_to_ptr(array_list->array[k]));
  }

  array_list_destroy(array_list);
}
void array_list_destroy_and(ArrayList * array_list, void (*function)(Any))
{
  assert(array_list);
  assert(array_list->base.open_traversals == 0);

  for (unsigned int k = 0; k < array_list->size; k++)
  {
    free(any_to_ptr(array_list->array[k]));
  }

  array_list_destroy(array_list);
}



unsigned int array_list_size(ArrayList * array_list)
{
  assert(array_list);

  sem_wait(&array_list->base.mutex);

  unsigned int ret = array_list->size;

  sem_post(&array_list->base.mutex);


  return ret;
}


Any array_list_get(ArrayList * array_list, unsigned int index)
{
  assert(array_list);

  sem_wait(&array_list->base.mutex);
  assert(index < array_list->size);
  Any ret;

  ret = array_list->array[index];

  sem_post(&array_list->base.mutex);


  return ret;
}

void array_list_add(ArrayList * array_list, Any element)
{
  assert(array_list);

  sem_wait(&array_list->base.mutex);
  assert(array_list->base.open_traversals == 0);

  array_list_resize(array_list, array_list->size + 1);
  array_list->array[array_list->size] = element;
  array_list->size++;


  sem_post(&array_list->base.mutex);
}

void array_list_add_range(ArrayList * array_list, List * range)
{
  assert(array_list);

  sem_wait(&array_list->base.mutex);
  assert(array_list->base.open_traversals == 0);

  if (range->type == LIST_TYPE_ARRAY_LIST)
  {
    sem_wait(&range->mutex);
    array_list_resize(
        array_list,
        array_list->size + ((ArrayList *) range)->size
      );
    memcpy(
        &array_list->array[array_list->size],
        ((ArrayList *) range)->array,
        sizeof(Any) * ((ArrayList *) range)->size
      );
    array_list->size += ((ArrayList *) range)->size;
    sem_post(&range->mutex);
  }
  else
  {
    array_list_resize(
        array_list,
        array_list->size + list_size(range)
      );
    unsigned int top = array_list->size;

    ListTraversal * traversal = list_get_traversal(range);
    while (!list_traversal_completed(traversal))
    {
      Any value = list_traversal_next(traversal);
      array_list->array[top++] = value;
    }

    array_list->size += list_size(range);

  }

  sem_post(&array_list->base.mutex);

}

void array_list_set(ArrayList * array_list, unsigned int index, Any element)
{
  assert(array_list);

  sem_wait(&array_list->base.mutex);
  assert(array_list->base.open_traversals == 0);
  assert(index < array_list->size);

  array_list->array[index] = element;

  sem_post(&array_list->base.mutex);
}

Any array_list_remove_at(ArrayList * array_list, unsigned int index)
{
  assert(array_list);

  sem_wait(&array_list->base.mutex);
  assert(array_list->base.open_traversals == 0);
  assert(index < array_list->size);

  Any ret = array_list->array[index];

  for (unsigned int k = index; k < array_list->size - 1; k++)
  {
    array_list->array[k] = array_list->array[k + 1];
  }

  array_list_resize(array_list, array_list->size - 1);
  array_list->size--;

  sem_post(&array_list->base.mutex);

  return ret;
}

void array_list_clear(ArrayList * array_list)
{
  assert(array_list);

  sem_wait(&array_list->base.mutex);

  array_list_resize(array_list, 0);
  array_list->size = 0;

  sem_post(&array_list->base.mutex);

}

Any * array_list_to_array(ArrayList * array_list)
{
  assert(array_list);

  sem_wait(&array_list->base.mutex);

  if (array_list->size == 0)
  {
    sem_post(&array_list->base.mutex);
    return NULL;
  }

  Any * ret = (Any *) malloc(sizeof(Any) * array_list->size);
  assert(ret);

  memcpy(ret, array_list->array, sizeof(Any) * array_list->size);

  sem_post(&array_list->base.mutex);

  return ret;
}

ArrayList * array_list_sub_list(
    ArrayList * array_list,
    unsigned int start,
    unsigned int end)
{
  assert(array_list);
  assert(start <= end);

  if (start == end)
  {
      return array_list_new();
  }

  sem_wait(&array_list->base.mutex);

  assert(end <= array_list->size);

  ArrayList * ret = array_list_new();


  array_list_resize(ret, end - start);

  memcpy(
    ret->array,
    &array_list->array[start],
    sizeof(Any) * (end - start)
    );



  ret->size = end - start;


  sem_post(&array_list->base.mutex);


  return ret;
}

ArrayList * array_list_clone(ArrayList * array_list)
{
  assert(array_list);

  sem_wait(&array_list->base.mutex);

  ArrayList * ret = array_list_new();
  array_list_resize(ret, array_list->size);

  memcpy(
      ret->array,
      array_list->array,
      sizeof(Any) * array_list->size
    );

  ret->size = array_list->size;

  sem_post(&array_list->base.mutex);

  return ret;
}

char * array_list_to_string(ArrayList * array_list)
{
  assert(array_list);
  
  if (array_list->size == 0)
    return strings_clone("[]");

  char * buffer;

  StringBuilder * sb = string_builder_new();
  string_builder_append(sb, "[ ");
  
  buffer = any_get_string_representation(array_list->array[0]);
  string_builder_append(sb, buffer);
  free(buffer);
  
  for (unsigned int k = 1; k < array_list->size; k++)
  {
    buffer = any_get_string_representation(array_list->array[k]);
    string_builder_append(sb, ", ");
    string_builder_append(sb, buffer);
    free(buffer);
  }

  string_builder_append(sb, " ]");

  return string_builder_to_string_destroy(sb);
}


/* end of methods for ArrayList */




/* methods for ArrayListTraversal */

ArrayListTraversal * array_list_get_traversal(ArrayList * array_list)
{
  assert(array_list);

  ArrayListTraversal * ret = (ArrayListTraversal *) malloc(sizeof(ArrayListTraversal));
  assert(ret);

  ret->base.type = LIST_TYPE_ARRAY_LIST;
  ret->base.list = (List *) array_list;
  ret->base.list_traversal_destroy = (void (*)(ListTraversal *)) array_list_traversal_destroy;
  ret->base.list_traversal_next = (Any (*)(ListTraversal *)) array_list_traversal_next;
  ret->base.list_traversal_completed = (bool (*)(ListTraversal *)) array_list_traversal_completed;

  ret->position = 0;

  sem_wait(&array_list->base.mutex);

  array_list->base.open_traversals++;

  sem_post(&array_list->base.mutex);

  return ret;
}

void array_list_traversal_destroy(ArrayListTraversal * array_list_traversal)
{
  assert(array_list_traversal);

  sem_wait(&array_list_traversal->base.list->mutex);

  array_list_traversal->base.list->open_traversals--;

  sem_post(&array_list_traversal->base.list->mutex);


  free(array_list_traversal);
}

Any array_list_traversal_next(ArrayListTraversal * array_list_traversal)
{
  assert(array_list_traversal);
  assert(!array_list_traversal_completed(array_list_traversal));

  return ((ArrayList *) array_list_traversal->base.list)->array[array_list_traversal->position++];
}

bool array_list_traversal_completed(ArrayListTraversal * array_list_traversal)
{
  assert(array_list_traversal);

  bool ret = array_list_traversal->position >= ((ArrayList *) array_list_traversal->base.list)->size;
  if (ret)
    array_list_traversal_destroy(array_list_traversal);

  return ret;
}


/* end of methods for ArrayListtTraversal */
