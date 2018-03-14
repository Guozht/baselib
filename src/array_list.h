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


#ifndef __BASELIB_ARRAY_LIST
#define __BASELIB_ARRAY_LIST


#include "any.h"
#include "list.h"


struct ArrayList;
typedef struct ArrayList ArrayList;

struct ArrayListTraversal;
typedef struct ArrayListTraversal ArrayListTraversal;


ArrayList * array_list_new();

void array_list_destroy(ArrayList * array_list);
void array_list_destroy_and_free(ArrayList * array_list);
void array_list_destroy_and_user_free(ArrayList * array_list, void (*callback)(void *));
void array_list_destroy_and(ArrayList * array_list, void (*function)(Any));

unsigned int array_list_size(ArrayList * array_list);


bool array_list_contains(ArrayList * array_list, Any any);

Any array_list_get(ArrayList * array_list, unsigned int index);
char array_list_get_char(ArrayList * array_list, unsigned int index);
int array_list_get_int(ArrayList * array_list, unsigned int index);
char * array_list_get_str(ArrayList * array_list, unsigned int index);
void * array_list_get_ptr(ArrayList * array_list, unsigned int index);

void array_list_add(ArrayList * array_list, Any element);
void array_list_add_range(ArrayList * array_list, List * range);
void array_list_set(ArrayList * array_list, unsigned int index, Any element);
void array_list_insert(ArrayList * array_list, unsigned int index, Any element);
void array_list_insert_range(ArrayList * array_list, unsigned int index, List * range);

Any array_list_remove_at(ArrayList * array_list, unsigned int index);
unsigned int array_list_remove(ArrayList * array_list, Any any);
unsigned int array_list_remove_and_free(ArrayList * array_list, Any any);


void array_list_swap(ArrayList * array_list, unsigned int index_a, unsigned int index_b);
void array_list_reposition(ArrayList * array_list, unsigned int from_index, unsigned int to_index);


void array_list_clear(ArrayList * array_list);
void array_list_clear_and_free(ArrayList * array_list);
void array_list_clear_and_user_free(ArrayList * array_list, void (*callback)(void *));
void array_list_clear_and(ArrayList * array_list, void (*function)(Any));


Any * array_list_to_array(ArrayList * array_list);

ArrayList * array_list_sub_list(ArrayList * array_list, unsigned int start, unsigned int end);
ArrayList * array_list_clone(ArrayList * array_list);

char * array_list_to_string(ArrayList * array_list);

void array_list_foreach(ArrayList * array_list, void (*function)(Any));

ArrayListTraversal * array_list_get_traversal(ArrayList * array_list);

void array_list_traversal_destroy(ArrayListTraversal * array_list_traversal);

Any array_list_traversal_next(ArrayListTraversal * array_list_traversal);
char array_list_traversal_next_char(ArrayListTraversal * array_list_traversal);
int array_list_traversal_next_int(ArrayListTraversal * array_list_traversal);
char * array_list_traversal_next_str(ArrayListTraversal * array_list_traversal);
void * array_list_traversal_next_ptr(ArrayListTraversal * array_list_traversal);

bool array_list_traversal_completed(ArrayListTraversal * array_list_traversal);



#endif
