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


#ifndef __BASELIB_ISO_8859_H
#define __BASELIB_ISO_8859_H


#include <stdbool.h>
#include <stdint.h>
#include <sys/types.h>

#include "charset.h"
#include "list.h"

int iso_8859_read(
  Charset encoding,
  char * string,
  uint32_t * code_point);

int iso_8859_write(
  Charset encoding,
  uint32_t code_point,
  char * string);


uint32_t * iso_8859_read_string(
  Charset encoding,
  char * string,
  size_t string_length,
  size_t * code_points_length_ptr);

char * iso_8859_write_string(
  Charset encoding,
  uint32_t * code_points,
  size_t code_points_length,
  size_t * string_length_ptr);

bool iso_8859_is_well_formed(
  Charset encoding,
  char * string,
  size_t string_length);
bool iso_8859_can_be_represented(
  Charset encoding,
  uint32_t * code_points,
  size_t code_points_length);

List * iso_8859_get_representable_code_points_list(
  Charset encoding
  );


#endif


