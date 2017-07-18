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


#include "linked_list.h"

#include "list_struct.h"
#include "list_type.h"
#include "list.h"
#include "any.h"

#include <assert.h>
#include <stdlib.h>
#include <semaphore.h>


struct LinkedListNode
{
  struct LinkedListNode * next;
  Any value;
};


struct LinkedList
{
  List base;
  struct LinkedListNode
    * start,
    * end;
  unsigned int size;
};

struct LinkedListTraversal
{
  ListTraversal base;
  struct LinkedListNode * current;
};






/* INTERNAL METHODS */

static struct LinkedListNode * linked_list_node_new(Any value, struct LinkedListNode * next)
{
  struct LinkedListNode * ret = (struct LinkedListNode *) malloc(sizeof(struct LinkedListNode));
  assert(ret);

  ret->value = value;
  ret->next = next;

  return ret;
}

/* END OF INTERNAL METHODS */



/* methods for LinkedList */

LinkedList * linked_list_new()
{
  LinkedList * ret = (LinkedList *) malloc(sizeof(LinkedList));
  assert(ret);

  ret->base.type = LIST_TYPE_LINKED_LIST;
  ret->base.open_traversals = 0;

  ret->base.list_destroy = (void (*)(List *)) linked_list_destroy;
  ret->base.list_size = (unsigned int (*)(List *)) linked_list_size;
  ret->base.list_get = (Any (*)(List *, unsigned int)) linked_list_get;
  ret->base.list_add = (void (*)(List *, Any)) linked_list_add;
  ret->base.list_set = (void (*)(List *, unsigned int, Any)) linked_list_set;
  ret->base.list_remove = (Any (*)(List *, unsigned int)) linked_list_remove;
  ret->base.list_get_traversal = (ListTraversal * (*)(List *)) linked_list_get_traversal;

  ret->start = NULL;
  ret->end = NULL;
  ret->size = 0;

  sem_init(&ret->base.mutex, 0, 1);

  return ret;
}
void linked_list_destroy(LinkedList * linked_list)
{
  assert(linked_list);
  assert(linked_list->base.open_traversals == 0);

  sem_destroy(&linked_list->base.mutex);

  struct LinkedListNode * current = linked_list->start;

  while (current)
  {
    struct LinkedListNode * hold = current;
    current = hold->next;
    free(hold);
  }

  free(linked_list);
}


unsigned int linked_list_size(LinkedList * linked_list)
{
  assert(linked_list);

  sem_wait(&linked_list->base.mutex);

  unsigned int ret = linked_list->size;

  sem_post(&linked_list->base.mutex);

  return ret;
}



Any linked_list_get(LinkedList * linked_list, unsigned int index)
{
  assert(linked_list);

  sem_wait(&linked_list->base.mutex);

  assert(index < linked_list->size);
  struct LinkedListNode * current = linked_list->start;

  for (unsigned int k = 0; k < index; k++)
  {
    current = current->next;
  }

  Any ret = current->value;

  sem_post(&linked_list->base.mutex);

  return ret;
}


void linked_list_add(LinkedList * linked_list, Any element)
{
  assert(linked_list);

  sem_wait(&linked_list->base.mutex);
  assert(linked_list->base.open_traversals == 0);

  struct LinkedListNode * node = linked_list_node_new(element, NULL);

  if (linked_list->size == 0)
  {
    linked_list->start = node;
    linked_list->end = node;
  }
  else
  {
    linked_list->end->next = node;
    linked_list->end = node;
  }

  linked_list->size++;

  sem_post(&linked_list->base.mutex);
}

void linked_list_set(LinkedList * linked_list, unsigned int index, Any element)
{

  assert(linked_list);

  sem_wait(&linked_list->base.mutex);
  assert(linked_list->base.open_traversals == 0);
  assert(index < linked_list->size);

  struct LinkedListNode * current = linked_list->start;

  for (unsigned int k = 0; k < index; k++)
  {
    current = current->next;
  }

  current->value = element;

  sem_post(&linked_list->base.mutex);
}


Any linked_list_remove(LinkedList * linked_list, unsigned int index)
{

  assert(linked_list);

  sem_wait(&linked_list->base.mutex);
  assert(linked_list->base.open_traversals == 0);
  assert(index < linked_list->size);

  Any ret;
  ret.ptr = NULL;

  if (linked_list->size == 1)
  {
    ret = linked_list->start->value;
    free(linked_list->start);
    linked_list->start = NULL;
    linked_list->end = NULL;
  }
  else
  {
    struct LinkedListNode
      * last = NULL,
      * current = linked_list->start;

    for (unsigned int k = 0; k < index; k++)
    {
      last = current;
      current = current->next;
    }

    if (last == NULL) /* ergo, is first */
    {
      linked_list->start = current->next;
      ret = current->value;
      free(current);
    }
    else if (current->next == NULL) /* ergo, is last */
    {
      free(current);
      linked_list->end = last;
      last->next = NULL;
    }
    else
    {
      last->next = current->next;
      ret = current->value;
      free(current);
    }
  }


  linked_list->size--;
  sem_post(&linked_list->base.mutex);

  return ret;
}

/* end of methods for LinkedList */

/* methods for LinkedListTraversal */

LinkedListTraversal * linked_list_get_traversal(LinkedList * linked_list)
{
  assert(linked_list);

  LinkedListTraversal * ret = (LinkedListTraversal *) malloc(sizeof(LinkedListTraversal));
  assert(ret);

  ret->base.type = LIST_TYPE_LINKED_LIST;
  ret->base.list = (List *) linked_list;
  ret->base.list_traversal_destroy = (void (*)(ListTraversal *)) linked_list_traversal_destroy;
  ret->base.list_traversal_next = (Any (*)(ListTraversal *)) linked_List_traversal_next;
  ret->base.list_traversal_completed = (bool (*)(ListTraversal *)) linked_list_traversal_completed;

  sem_wait(&linked_list->base.mutex);

  ret->current = linked_list->start;
  linked_list->base.open_traversals++;

  sem_post(&linked_list->base.mutex);

  return ret;
}

void linked_list_traversal_destroy(LinkedListTraversal * linked_list_traversal)
{
  assert(linked_list_traversal);

  sem_wait(&linked_list_traversal->base.list->mutex);

  linked_list_traversal->base.list->open_traversals--;

  sem_post(&linked_list_traversal->base.list->mutex);

  free(linked_list_traversal);
}


Any linked_List_traversal_next(LinkedListTraversal * linked_list_traversal)
{
  assert(linked_list_traversal);
  assert(!linked_list_traversal_completed(linked_list_traversal));

  Any ret = linked_list_traversal->current->value;

  linked_list_traversal->current = linked_list_traversal->current->next;

  return ret;
}

bool linked_list_traversal_completed(LinkedListTraversal * linked_list_traversal)
{
  assert(linked_list_traversal);

  bool ret = linked_list_traversal->current == NULL;
  if (ret)
    linked_list_traversal_destroy(linked_list_traversal);

  return ret;
}


/* end of methods for LinkedListTraversal */
