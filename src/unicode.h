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

#ifndef __BASELIB_UNICODE_H
#define __BASELIB_UNICODE_H

#include <sys/types.h>
#include <stdint.h>
#include <stdbool.h>

#include "unicode_encoding_type.h"

/* UNICODE */

char * unicode_get_block_name(uint32_t code_point);
bool unicode_is_valid_code_point(uint32_t code_point);


/* GENERIC */

unsigned int unicode_code_point_byte_requirement(
  UnicodeEncodingType encoding,
  uint32_t code_point);
bool unicode_is_well_formed(
  UnicodeEncodingType encoding,
  char * string,
  size_t string_length);

unsigned int unicode_string_length(
  UnicodeEncodingType encoding,
  char * string,
  size_t string_length);

int unicode_read(
  UnicodeEncodingType encoding,
  char * string,
  uint32_t * code_point);
int unicode_write(
  UnicodeEncodingType encoding,
  uint32_t code_point,
  char * string);

uint32_t * unicode_read_string(
  UnicodeEncodingType encoding,
  char * string,
  size_t string_length,
  size_t * code_points_length_ptr);
char * unicode_write_string(
  UnicodeEncodingType encoding,
  uint32_t * code_points,
  size_t code_points_length,
  size_t * string_length_ptr);




/* UTF-7 */


unsigned int unicode_code_point_byte_requirement_utf7(uint32_t code_point);
bool unicode_is_well_formed_utf7(char * string, size_t string_length);

unsigned int unicode_string_length_utf7(char * string, size_t string_length);

int unicode_read_utf7(char * string, uint32_t * code_point);
int unicode_write_utf7(uint32_t code_point, char * string);

uint32_t * unicode_read_string_utf7(char * string, size_t string_length, size_t * code_points_length_ptr);
char * unicode_write_string_utf7(uint32_t * code_points, size_t code_points_length, size_t * string_length_ptr);


/* UTF-8 */

unsigned int unicode_code_point_byte_requirement_utf8(uint32_t code_point);
bool unicode_is_well_formed_utf8(char * string, size_t string_length);

unsigned int unicode_string_length_utf8(char * string, size_t string_length);

int unicode_read_utf8(char * string, uint32_t * code_point);
int unicode_write_utf8(uint32_t code_point, char * string);

uint32_t * unicode_read_string_utf8(char * string, size_t string_length, size_t * code_points_length_ptr);
char * unicode_write_string_utf8(uint32_t * code_points, size_t code_points_length, size_t * string_length_ptr);


/* UTF-16 */

unsigned int unicode_code_point_byte_requirement_utf16(uint32_t code_point);

bool unicode_is_well_formed_utf16(char * string, size_t string_length);
bool unicode_is_well_formed_utf16be(char * string, size_t string_length);
bool unicode_is_well_formed_utf16le(char * string, size_t string_length);


unsigned int unicode_string_length_utf16(char * string, size_t string_length);
unsigned int unicode_string_length_utf16be(char * string, size_t string_length);
unsigned int unicode_string_length_utf16le(char * string, size_t string_length);

int unicode_read_utf16be(char * string, uint32_t * code_point);
int unicode_read_utf16le(char * string, uint32_t * code_point);

int unicode_write_utf16(uint32_t code_point, char * string);
int unicode_write_utf16be(uint32_t code_point, char * string);
int unicode_write_utf16le(uint32_t code_point, char * string);


uint32_t * unicode_read_string_utf16(char * string, size_t string_length, size_t * code_point_length_ptr);
uint32_t * unicode_read_string_utf16be(char * string, size_t string_length, size_t * code_point_length_ptr);
uint32_t * unicode_read_string_utf16le(char * string, size_t string_length, size_t * code_point_length_ptr);

/* expects null terminlated code point list */
char * unicode_write_string_utf16(uint32_t * code_points, size_t code_points_length, size_t * string_length_ptr);
char * unicode_write_string_utf16be(uint32_t * code_points, size_t code_points_length, size_t * string_length_ptr);
char * unicode_write_string_utf16le(uint32_t * code_points, size_t code_points_length, size_t * string_length_ptr);

char * unicode_write_string_utf16_without_bom(uint32_t * code_points, size_t code_points_length, size_t * string_length_ptr);
char * unicode_write_string_utf16be_without_bom(uint32_t * code_points, size_t code_points_length, size_t * string_length_ptr);
char * unicode_write_string_utf16le_without_bom(uint32_t * code_points, size_t code_points_length, size_t * string_length_ptr);



/* UTF-32 */

unsigned int unicode_code_point_byte_requirement_utf32(uint32_t code_point);

bool unicode_is_well_formed_utf32(char * string, size_t string_length);
bool unicode_is_well_formed_utf32be(char * string, size_t string_length);
bool unicode_is_well_formed_utf32le(char * string, size_t string_length);

unsigned int unicode_string_length_utf32(char * string, size_t string_length);
unsigned int unicode_string_length_utf32be(char * string, size_t string_length);
unsigned int unicode_string_length_utf32le(char * string, size_t string_length);

int unicode_read_utf32be(char * string, uint32_t * code_point);
int unicode_read_utf32le(char * string, uint32_t * code_point);

int unicode_write_utf32(uint32_t code_point, char * string);
int unicode_write_utf32be(uint32_t code_point, char * string);
int unicode_write_utf32le(uint32_t code_point, char * string);

uint32_t * unicode_read_string_utf32(char * string, size_t string_length, size_t * code_points_length_ptr);
uint32_t * unicode_read_string_utf32be(char * string, size_t string_length, size_t * code_points_length_ptr);
uint32_t * unicode_read_string_utf32le(char * string, size_t string_length, size_t * code_points_length_ptr);

/* expects null terminlated code point list */
char * unicode_write_string_utf32(uint32_t * code_points, size_t code_points_length, size_t * string_length_ptr);
char * unicode_write_string_utf32be(uint32_t * code_points, size_t code_points_length, size_t * string_length_ptr);
char * unicode_write_string_utf32le(uint32_t * code_points, size_t code_points_length, size_t * string_length_ptr);

char * unicode_write_string_utf32_without_bom(uint32_t * code_points, size_t code_points_length, size_t * string_length_ptr);
char * unicode_write_string_utf32be_without_bom(uint32_t * code_points, size_t code_points_length, size_t * string_length_ptr);
char * unicode_write_string_utf32le_without_bom(uint32_t * code_points, size_t code_points_length, size_t * string_length_ptr);



#endif
