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


#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h>

#include "any.h"
#include "list.h"
#include "mtest.h"
#include "utilities.h"

#include "list_tools.h"


static void list_tools_merge_sort(
    List * list,
    int (*comparator)(Any, Any),
    unsigned int start,
    unsigned int end
  )
{
  unsigned int
    length = end - start,
    half,
    low_selection_index,
    high_selection_index,
    array_insertion_index;
  Any
    low,
    high;
  Any
    array [length];
  bool
    low_valid,
    high_valid;
  int relative;

  switch (length)
  {
    case 0:
    case 1:
      return;
    case 2:
      relative = comparator(list_get(list, start), list_get(list, start + 1));
      if (relative < 0)
        list_swap(list, start, start + 1);
      return;
    default:
      break;
  }

  half = length / 2 + start;
  list_tools_merge_sort(list, comparator, start, half);
  list_tools_merge_sort(list, comparator, half, end);

  low_selection_index = start;
  high_selection_index = half;
  array_insertion_index = 0;

  low_valid = false;
  high_valid = false;

  while (low_selection_index < half && high_selection_index < end)
  {
    if (!low_valid)
      low = list_get(list, low_selection_index);
    if (!high_valid)
      high = list_get(list, high_selection_index);

    relative = comparator(low, high);
    if (relative >= 0)
    {
      array[array_insertion_index] = low;
      low_valid = false;
      high_valid = true;
      low_selection_index++;
    }
    else
    {
      array[array_insertion_index] = high;
      low_valid = true;
      high_valid = false;
      high_selection_index++;
    }

    array_insertion_index++;
  }

  while (low_selection_index < half)
  {
    array[array_insertion_index++] = list_get(list, low_selection_index++);
  }

  while (high_selection_index < end)
  {
    array[array_insertion_index++] = list_get(list, high_selection_index++);
  }

  for (unsigned int k = start; k < end; k++)
  {
    list_set(list, k, array[k - start]);
  }
}
static void list_tools_quick_sort(
    List * list,
    int (*comparator)(Any, Any),
    unsigned int start,
    unsigned int end
  )
{
  int
    relative;
  unsigned int
    length = end - start,
    partition_index;
  Any
    pivot_value;

  switch (length)
  {
    case 0:
    case 1:
      return;
    case 2:
      relative = comparator(list_get(list, start), list_get(list, start + 1));
      if (relative < 0)
        list_swap(list, start, start + 1);
      return;
    default:
      break;
  }

  partition_index = start;
  pivot_value = list_get(list, end - 1);

  for (unsigned int k = start; k < end - 1; k++)
  {
    if (comparator(list_get(list, k), pivot_value) >= 0)
      list_swap(list, partition_index++, k);
  }

  list_swap(list, partition_index, end - 1);

  list_tools_quick_sort(list, comparator, start, partition_index);
  list_tools_quick_sort(list, comparator, partition_index + 1, end);
}
static void list_tools_heap_sort(List * list, int (*comparator)(Any, Any))
{
  assert(0); /* NOT YET IMPLEMENTED */
}
static void list_tools_insertion_sort(List * list, int (*comparator)(Any, Any))
{
  unsigned int
    size = list_size(list),
    insertion_index;
  Any
    k_value,
    i_value;

  for (unsigned int k = 1; k < size; k++)
  {
    k_value = list_get(list, k);
    i_value = list_get(list, k - 1);

    if (comparator(k_value, i_value) <= 0)
      continue;

    insertion_index = k - 1;
    for (unsigned int i = k - 2; i != (unsigned int) -1; i--)
    {
      if (comparator(k_value, list_get(list, i)) <= 0)
        i = 0;
      else
        insertion_index--;
    }

    if (insertion_index == k - 1)
      list_swap(list, k, k - 1);
    else
     list_reposition(list, k, insertion_index);
  }
}
static void list_tools_intro_sort(List * list, int (*comparator)(Any, Any))
{
  assert(0); /* NOT YET IMPLEMENTED */
}
static void list_tools_selection_sort(List * list, int (*comparator)(Any, Any))
{
  unsigned int
    size = list_size(list),
    best_index;
  Any
    best_value,
    temp_value;

  if (size == 0)
    return;

  for (unsigned int k = 0; k < size - 1; k++)
  {
    best_value = list_get(list, k);
    best_index = k;

    for (unsigned int i = k + 1; i < size; i++)
    {
      temp_value = list_get(list, i);
      if (comparator(best_value, temp_value) < 0)
      {
        best_value = temp_value;
        best_index = i;
      }
    }

    list_swap(list, k, best_index);
  }
}
static void list_tools_tim_sort(List * list, int (*comparator)(Any, Any))
{
  assert(0); /* NOT YET IMPLEMENTED */
}
static void list_tools_cube_sort(List * list, int (*comparator)(Any, Any))
{
  assert(0); /* NOT YET IMPLEMENTED */
}
static void list_tools_shell_sort(List * list, int (*comparator)(Any, Any))
{
  assert(0); /* NOT YET IMPLEMENTED */
}
static void list_tools_smooth_sort(List * list, int (*comparator)(Any, Any))
{
  assert(0); /* NOT YET IMPLEMENTED */
}
static void list_tools_block_sort(List * list, int (*comparator)(Any, Any))
{
  assert(0); /* NOT YET IMPLEMENTED */
}


void list_tools_reverse(List * list)
{
  assert(list);

  Any * array;
  unsigned int array_length;

  array = list_to_array(list);
  array_length = list_size(list);

  for (unsigned int k = 0; k < array_length; k++)
  {
    list_set(list, array_length - k - 1, array[k]);
  }

  _free(array);
}

void list_tools_sort(List * list, int (*comparator)(Any, Any))
{
  list_tools_sort_with_method(list, comparator, SORT_METHOD_MERGE);
}

void list_tools_sort_with_method(
    List * list,
    int (*comparator)(Any, Any),
    SortMethod method
  )
{
  assert(list); 
  switch (method)
  {
    case SORT_METHOD_MERGE:
      list_tools_merge_sort(list, comparator, 0, list_size(list));
      break;
    case SORT_METHOD_QUICK:
      list_tools_quick_sort(list, comparator, 0, list_size(list));
      break;
    case SORT_METHOD_HEAP:
      list_tools_heap_sort(list, comparator);
      break;
    case SORT_METHOD_INSERTION:
      list_tools_insertion_sort(list, comparator);
      break;
    case SORT_METHOD_INTRO:
      list_tools_intro_sort(list, comparator);
      break;
    case SORT_METHOD_SELECTION:
      list_tools_selection_sort(list, comparator);
      break;
    case SORT_METHOD_TIM:
      list_tools_tim_sort(list, comparator);
      break;
    case SORT_METHOD_CUBE:
      list_tools_cube_sort(list, comparator);
      break;
    case SORT_METHOD_SHELL:
      list_tools_shell_sort(list, comparator);
      break;
    case SORT_METHOD_SMOOTH:
      list_tools_smooth_sort(list, comparator);
      break;
    case SORT_METHOD_BLOCK:
      list_tools_block_sort(list, comparator);
      break;
    default:
      assert(0); /* UNKNOWN SORTING ALGORITHM */
  }
}



void list_tools_shuffle(List * list)
{
  list_tools_shuffle_with_seed(list, (unsigned int) utilities_unix_millisecond());
}
/* implements Fisher-Yates shuffle */
void list_tools_shuffle_with_seed(List * list, unsigned int seed)
{
  assert(list);

  unsigned int k, random_index;
  for (k = list_size(list) - 1; k > 0; k--)
  {
    random_index = utilities_random_integer(0, k + 1, &seed);
    list_swap(list, k, random_index);
  }

}


List * list_tools_from_array(
    void * array, unsigned int array_length,
    enum AnyType element_type
  )
{
  assert(0); /* NOT YET IMPLEMENTED */
}
List * list_tools_from_any_array(
    Any * array, unsigned int array_length
  )
{
  assert(0); /* NOT YET IMPLEMENTED */
}


static void list_tools_max_heapify(List * list, int (*comparator)(Any, Any))
{
  assert(0);
}

static void list_tools_min_heapify(List * list, int (*comparator)(Any, Any))
{
  assert(0);
}

void list_tools_heapify(
    List * list,
    int (*comparator)(Any, Any),
    HeapQuality quality
  )
{
  assert(list);

  switch (quality)
  {

    case HEAP_QUALITY_MAX:
      list_tools_max_heapify(list, comparator);
      break;
    case HEAP_QUALITY_MIN:
      list_tools_min_heapify(list, comparator);
      break;

    default:
      assert(0);

  }

}


