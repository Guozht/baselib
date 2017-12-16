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
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h> /* for size_t */



unsigned int unicode_code_point_byte_requirement_utf7(uint32_t code_point)
{
  assert(0); /* NOT YET IMPLEMENTED */
}
bool unicode_is_well_formed_utf7(char * string, size_t string_length)
{
  assert(0); /* NOT YET IMPLEMENTED */
}

unsigned int unicode_string_length_utf7(char * string, size_t string_length)
{
  assert(0); /* NOT YET IMPLEMENTED */
}

int unicode_read_utf7(char * string, uint32_t * code_point)
{
  assert(0); /* NOT YET IMPLEMENTED */
}
int unicode_write_utf7(uint32_t code_point, char * string)
{
  assert(0); /* NOT YET IMPLEMENTED */
}

uint32_t * unicode_read_string_utf7(char * string, size_t string_length, size_t * code_points_length_ptr)
{
  assert(0); /* NOT YET IMPLEMENTED */
}
char * unicode_write_string_utf7(uint32_t * code_points, size_t code_points_length, size_t * string_length_ptr)
{
  assert(0); /* NOT YET IMPLEMENTED */
}
