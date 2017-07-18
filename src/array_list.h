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


#ifndef __ARRAY_LIST
#define __ARRAY_LIST


#include "any.h"


struct ArrayList;
typedef struct ArrayList ArrayList;

struct ArrayListTraversal;
typedef struct ArrayListTraversal ArrayListTraversal;



ArrayList * array_list_new();
void array_list_destroy(ArrayList * array_list);


unsigned int array_list_size(ArrayList * array_list);


Any array_list_get(ArrayList * array_list, unsigned int index);

void array_list_add(ArrayList * array_list, Any element);
void array_list_set(ArrayList * array_list, unsigned int index, Any element);

Any array_list_remove(ArrayList * array_list, unsigned int index);



ArrayListTraversal * array_list_get_traversal(ArrayList * array_list);
void array_list_traversal_destroy(ArrayListTraversal * array_list_traversal);

Any array_list_traversal_next(ArrayListTraversal * array_list_traversal);
bool array_list_traversal_completed(ArrayListTraversal * array_list_traversal);



#endif
