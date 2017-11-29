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


/* WARNING:
 *
 * The methods and/or types defined and/or declared  within this file
 * are not guaranteed to remain consistent in later versions
 *
 */



#ifndef __BASELIB_UTILITIES_H
#define __BASELIB_UTILITIES_H

#include <stdbool.h>
#include <string.h>

#include "endianness.h"

long utilities_lmin(long l0, long l1);
long utilities_lmax(long l0, long l1);

Endianness utilities_get_endianness();

unsigned int utilities_null_terminated_length(void * array, size_t element_size);


size_t utilities_round_size_upward(size_t s, size_t mod);
size_t utilities_multiply_round_up(size_t s, double ratio);


#endif


