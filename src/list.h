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



#ifndef __BASELIB_LIST_H
#define __BASELIB_LIST_H


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
void list_destroy_and_user_free(List * list, void (*callback)(void *));
void list_destroy_and(List * list, void (*function)(Any));

unsigned int list_size(List * list);
bool list_has_open_traversals(List * list);

bool list_contains(List * list, Any any);

Any list_get(List * list, unsigned int index);

char list_get_char(List * list, unsigned int index);
int list_get_int(List * list, unsigned int index);

char * list_get_str(List * list, unsigned int index);
void * list_get_ptr(List * list, unsigned int index);



void list_add(List * list, Any element);
void list_add_range(List * list, List * range);
void list_set(List * list, unsigned int index, Any element);
void list_insert(List * list, unsigned int index, Any element);
void list_insert_range(List * list, unsigned int index, List * range);

Any list_remove_at(List * list, unsigned int index);
unsigned int list_remove(List * list, Any any);
unsigned int list_remove_and_free(List * list, Any any);

void list_clear(List * list);
void list_clear_and_free(List * list);
void list_clear_and_user_free(List * list, void (*callback)(void *));
void list_clear_and(List * list, void (*function)(Any));

void list_swap(List * list, unsigned int index_a, unsigned int index_b);
void list_reposition(List * list, unsigned int from_index, unsigned int to_index);

Any * list_to_array(List * list);
List * list_sub_list(List * list, unsigned int start, unsigned int end);
List * list_clone(List * list);

char * list_to_string(List * list);


void list_foreach(List * list, void (*function)(Any));


ListTraversal * list_get_traversal(List * list);
void list_traversal_destroy(ListTraversal * list_traversal);

Any list_traversal_next(ListTraversal * list_traversal);

char list_traversal_next_char(ListTraversal * list_traversal);
int list_traversal_next_int(ListTraversal * list_traversal);
char * list_traversal_next_str(ListTraversal * list_traversal);
void * list_traversal_next_ptr(ListTraversal * list_traversal);

#define list_traversal_has_next(t) !list_traversal_completed(t)
bool list_traversal_completed(ListTraversal * list_traversal);


#endif
