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



#ifndef __LIST_H
#define __LIST_H


#include "list_type.h"
#include "any.h"

#include <stdbool.h>


struct List;
typedef struct List List;

struct ListTraversal;
typedef struct ListTraversal ListTraversal;


/* CONSTRUCTOR */
List * list_new(ListType type);

/* DESTRUCTOR */
void list_destroy(List * list);
void list_destroy_and_free(List * list);
void list_destroy_and(List * list, void (*function)(Any));

unsigned int list_size(List * list);
bool list_has_open_traversals(List * list);


Any list_get(List * list, unsigned int index);

void list_add(List * list, Any element);
void list_add_range(List * list, List * range);
void list_set(List * list, unsigned int index, Any element);

Any list_remove_at(List * list, unsigned int index);
unsigned int list_remove(List * list, Any any);
void list_clear(List * list);

Any * list_to_array(List * list);
List * list_sub_list(List * list, unsigned int start, unsigned int end);
List * list_clone(List * list);

char * list_to_string(List * list);


ListTraversal * list_get_traversal(List * list);
void list_traversal_destroy(ListTraversal * list_traversal);

Any list_traversal_next(ListTraversal * list_traversal);
bool list_traversal_completed(ListTraversal * list_traversal);


#endif
