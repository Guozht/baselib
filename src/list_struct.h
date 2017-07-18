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


#ifndef __LIST_STRUCT_H
#define __LIST_STRUCT_H

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
  unsigned int (*list_size)(struct List *);

  Any (*list_get)(struct List *, unsigned int);

  void (*list_add)(struct List *, Any);
  void (*list_set)(struct List *, unsigned int, Any);

  Any (*list_remove)(struct List *, unsigned int);

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