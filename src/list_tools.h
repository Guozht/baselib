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


#ifndef __BASELIB_LIST_TOOLS_H
#define __BASELIB_LIST_TOOLS_H

#include <sys/types.h>

enum SortMethod
{
  SORT_METHOD_MERGE,     /* TODO: IMPLEMENT ALL (OR MOST) OF THESE */
  SORT_METHOD_QUICK,
  SORT_METHOD_HEAP,
  SORT_METHOD_INSERTION,
  SORT_METHOD_INTRO,
  SORT_METHOD_SELECTION,
  SORT_METHOD_TIM,
  SORT_METHOD_CUBE,
  SORT_METHOD_SHELL,
  SORT_METHOD_SMOOTH,
  SORT_METHOD_BLOCK,
};
typedef enum SortMethod SortMethod;

enum HeapQuality
{
  HEAP_QUALITY_MAX,
  HEAP_QUALITY_MIN,
};
typedef enum HeapQuality HeapQuality;


void list_tools_reverse(List * list);

void list_tools_sort(List * list, int (*comparator)(Any, Any));
void list_tools_sort_with_method(List * list, int (*comparator)(Any, Any), SortMethod method);

void list_tools_shuffle(List * list);
void list_tools_shuffle_with_seed(List * list, unsigned int seed);


List * list_tools_from_array(
    void * array, unsigned int array_length,
    enum AnyType element_type 
  );
List * list_tools_from_any_array(
    Any * array, unsigned int array_length
  );

void list_tools_heapify(
    List * list,
    int (*comparator)(Any, Any),
    HeapQuality quality
  );


#endif

