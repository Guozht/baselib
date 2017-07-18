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



#ifndef __LINKED_LIST_H
#define __LINKED_LIST_H


struct LinkedList;
typedef struct LinkedList LinkedList;

struct LinkedListTraversal;
typedef struct LinkedListTraversal LinkedListTraversal;

#include "any.h"



LinkedList * linked_list_new();
void linked_list_destroy(LinkedList * linked_list);


unsigned int linked_list_size(LinkedList * linked_list);


Any linked_list_get(LinkedList * linked_list, unsigned int index);

void linked_list_add(LinkedList * linked_list, Any element);
void linked_list_set(LinkedList * linked_list, unsigned int index, Any element);

Any linked_list_remove(LinkedList * linked_list, unsigned int index);



LinkedListTraversal * linked_list_get_traversal(LinkedList * linked_list);
void linked_list_traversal_destroy(LinkedListTraversal * linked_list_traversal);

Any linked_List_traversal_next(LinkedListTraversal * linked_list_traversal);
bool linked_list_traversal_completed(LinkedListTraversal * linked_list_traversal);



#endif
