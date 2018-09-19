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


#ifndef __BASELIB_BASE64_H
#define __BASELIB_BASE64_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>


bool base64_is_valid_char(char c);

char * base64_encode(char * data, size_t data_size);
char * base64_encode_non_padded(char * data, size_t data_size);

char * base64_decode(char * data, size_t * decoded_size_ptr);
char * base64_decode_up_to(
  char * data, size_t data_length, size_t * decoded_size_ptr
  );

bool base64_is_well_formed(char * data);
bool base64_is_well_formed_up_to(char * data, size_t length);


#endif
