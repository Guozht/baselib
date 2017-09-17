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
#include "list.h"


struct ArrayList;
typedef struct ArrayList ArrayList;

struct ArrayListTraversal;
typedef struct ArrayListTraversal ArrayListTraversal;


/**
 * Create a new empty array list
 * object
 */
ArrayList * array_list_new();

/**
 * Destroys the array list and 
 * frees the memory allocated
 * to it
 */
void array_list_destroy(ArrayList * array_list);

/**
 * Destroys the array list and
 * frees the memory allocated
 * to it. This also frees
 * the values of the held by the
 * array as though they were pointers
 */
void array_list_destroy_and_free(ArrayList * array_list);

/**
 * Destroys the array list and 
 * frees the memory allocated 
 * to it. Will invoke the 
 * callback for each remaining 
 * element of the list
 */
void array_list_destroy_and(ArrayList * array_list, void (*function)(Any));


/**
 * Returns the size of the array
 */
unsigned int array_list_size(ArrayList * array_list);


/**
 * Returns the element in the specified
 * position of the array
 */
Any array_list_get(ArrayList * array_list, unsigned int index);


/**
 * Adds the specified element to the end of the array
 */
void array_list_add(ArrayList * array_list, Any element);

/**
 * Adds the elements of the specified list to end 
 * of the array
 */
void array_list_add_range(ArrayList * array_list, List * range);

/**
 * Sets the element into the specified index
 * overwriting whatever element was original
 * at that index
 */
void array_list_set(ArrayList * array_list, unsigned int index, Any element);


/**
 * Removes the element at the specified index
 * from the array
 */
Any array_list_remove_at(ArrayList * array_list, unsigned int index);

/**
 * Removes the element from the array
 */
unsigned int array_list_remove(ArrayList * array_list, Any any);

/**
 * Clears all elements fromt the array
 */
void array_list_clear(ArrayList * array_list);


/**
 * Returns an pointer to an standard
 * array of elements matching the elements
 * in the array list
 */
Any * array_list_to_array(ArrayList * array_list);

/**
 * Returns a sub-array of values formed
 * of the values within the array from
 * the specified start to the specified
 * end
 */
ArrayList * array_list_sub_list(ArrayList * array_list, unsigned int start, unsigned int end);

/**
 * Returns a shallow copy of the array
 */
ArrayList * array_list_clone(ArrayList * array_list);


/**
 * Returns a string representation of the array
 */
char * array_list_to_string(ArrayList * array_list);


/**
 * Returns a traversal object for the array
 */
ArrayListTraversal * array_list_get_traversal(ArrayList * array_list);

/**
 * Destroys the traversal object
 */
void array_list_traversal_destroy(ArrayListTraversal * array_list_traversal);


/**
 * Gets the next value of the traversal and
 * incriments the traversal's location
 */
Any array_list_traversal_next(ArrayListTraversal * array_list_traversal);

/**
 * Returns true if the traversal object has
 * reached the end of the array. If this
 * method is called, and it returns true,
 * it will have called destroy on the array
 */
bool array_list_traversal_completed(ArrayListTraversal * array_list_traversal);



#endif
