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



#include <stdbool.h>
#include <stdint.h>


#include "utilities.h"



long utilities_lmin(long l0, long l1)
{
  if (l0 < l1)
    return l0;
  else
    return l1;
}

long utilities_lmax(long l0, long l1)
{
  if (l0 > l1)
    return l0;
  else 
    return l1;
}


unsigned int utilities_uimin(unsigned int i0, unsigned int i1)
{
  if (i0 < i1)
    return i0;
  else
    return i1;
}


Endianness utilities_get_endianness()
{
  uint16_t a = 0xFF;
  if((*(uint8_t *) &a) == 0x0)
    return ENDIANNESS_BIG;
  else
    return ENDIANNESS_LITTLE;
}


unsigned int utilities_null_terminated_length(void * array, size_t element_size)
{
  unsigned int ret = 0;
  
  uint8_t comparrison [element_size];
  memset(comparrison, 0, element_size);
  
  /* cast purely to make the compiler shut up */
  while (memcmp(&((uint8_t *) array)[ret * element_size], comparrison, element_size))
    ret++;
  
  return ret;
}

size_t utilities_round_size_upward(size_t s, size_t mod)
{
  size_t v = s % mod;
  if (v == 0)
    return s;
  else
    return s + mod - v;
}

size_t utilities_multiply_round_up(size_t s, double ratio)
{
  double d = s * ratio;
  if (d != (int) d)
    return (int) d + 1;
  else
    return (int) d;
}

