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


#ifndef __BASELIB_LIST_STRUCT_H
#define __BASELIB_LIST_STRUCT_H

#include "list_type.h"
#include "any.h"

#include <stdbool.h>
#include <semaphore.h>

struct List
{

  ListType type;
  unsigned int open_traversals;
  sem_t mutex;

  void (*list_destroy)(struct List *);
  void (*list_destroy_and_free)(struct List *);
  void (*list_destroy_and_user_free)(struct List *, void (*callback)(void *));
  void (*list_destroy_and)(struct List *, void (*function)(Any));

  unsigned int (*list_size)(struct List *);

  Any (*list_get)(struct List *, unsigned int);

  void (*list_add)(struct List *, Any);
  void (*list_add_range)(struct List *, struct List *);
  void (*list_set)(struct List *, unsigned int, Any);

  Any (*list_remove_at)(struct List *, unsigned int);
  unsigned int (*list_remove)(struct List *, Any);
  void (*list_clear)(struct List *);
  void (*list_clear_and_free)(struct List *);
  void (*list_clear_and)(struct List *, void (*function)(Any));

  char * (*list_to_string)(struct List *);

  void (*list_foreach)(struct List *, void (*function)(Any));

  Any * (*list_to_array)(struct List *);
  struct List * (*list_sub_list)(struct List *, unsigned int start, unsigned int end);
  struct List * (*list_clone)(struct List *);

  struct ListTraversal * (*list_get_traversal)(struct List *);

};



struct ListTraversal
{

  ListType type;
  struct List * list;

  void (*list_traversal_destroy)(struct ListTraversal *);
  Any (*list_traversal_next)(struct ListTraversal *);
  bool (*list_traversal_completed)(struct ListTraversal *);

};



#endif
