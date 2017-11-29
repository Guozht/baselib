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
#include <stdint.h>
#include <stdlib.h>

#include "strings.h"
#include "endianness.h"
#include "unicode_encoding_type.h"
#include "utilities.h"

#include "unicode.h"


static uint32_t unicode_reverse_codepoint_utf32(uint32_t code_point, bool reverse)
{
  if (reverse)
    return 
      ((code_point << 24) & 0xFF000000) | 
      ((code_point << 8) & 0x00FF0000) |
      ((code_point >> 8) & 0x0000FF00) |
      ((code_point >> 24) & 0x000000FF);
  else
    return code_point;
    
}

static bool unicode_is_well_formed_utf32_imp(uint32_t * data, size_t data_length, bool reverse)
{
  for (int k = 0; k < data_length; k++)
   {
    if (!unicode_is_valid_code_point(unicode_reverse_codepoint_utf32(data[k], reverse)))
      return false;
  }
  
  return true;
}

static bool unicode_is_well_formed_utf32_with_endianness(
  char * string, 
  size_t string_length, 
  Endianness endianness, 
  bool * reverse_ptr,
  bool * remove_bom
  )
{
  if (string_length == 0)
    return true;
  if (string_length % 4 != 0)
    return false;
  
  Endianness system_endianness = utilities_get_endianness();
  uint32_t * data = (uint32_t *) string;

  bool reverse = system_endianness != endianness;
  
  if (unicode_reverse_codepoint_utf32(data[0], reverse) == 0x0000FEFF)
  {
    data = &data[1];
    string_length -= 4;
  
    if (remove_bom)
      *remove_bom = true;
  }
  else if (remove_bom)
    *remove_bom = false;
  
  if (reverse_ptr)
    *reverse_ptr = reverse;
  
  return unicode_is_well_formed_utf32_imp(data, string_length / 4, reverse);
}

static int unicode_read_utf32_imp(char * string, uint32_t * code_point, bool reverse)
{
  assert(string);
  assert(code_point);
  
  *code_point = unicode_reverse_codepoint_utf32(*(uint32_t *) string, reverse);
  if (unicode_is_valid_code_point(*code_point))
    return 4;
  else
    return -4;
}

static int unicode_write_utf32_imp(uint32_t code_point, char * string, bool reverse)
{
  assert(string);
  
  *((uint32_t *) string) = unicode_reverse_codepoint_utf32(code_point, reverse);
  return 4;
}

static uint32_t * unicode_read_string_utf32_imp(char * string, size_t string_length, size_t * code_points_length_ptr, bool reverse, bool remove_bom)
{
  assert(string);
  assert(code_points_length_ptr);

  if (string_length % 4 != 0)
    return NULL;
  else if (string_length == 0 || (string_length == 4 && remove_bom))
  {
    *code_points_length_ptr = 0;
    return NULL;
  }

  uint32_t * ret;
  size_t ret_length = string_length / 4;
  if (remove_bom)
    ret_length--;

  ret = (uint32_t *) malloc(sizeof(uint32_t) * (ret_length + 1));
  assert(ret);

  size_t ret_top = 0;
  for (size_t k = remove_bom ? 4 : 0; k < string_length; k += 4)
  {
    ret[ret_top++] = unicode_reverse_codepoint_utf32(*(uint32_t *) &string[k], reverse);
  }

  assert(ret_top == ret_length);

  ret[ret_length] = 0;
  *code_points_length_ptr = ret_length;

  return ret;
}

static char * unicode_write_string_utf32_imp(uint32_t * code_points, size_t code_points_length, size_t * string_length_ptr, bool reverse, bool add_bom)
{
  assert(code_points);
  assert(string_length_ptr);

  if (!add_bom && code_points_length == 0)
  {
    *string_length_ptr = 0;
    return NULL;
  }

  size_t 
    ret_length = code_points_length * 4 + (add_bom ? 4 : 0),
    ret_top = 0;
  char 
    * ret = (char *) malloc(sizeof(char) * (ret_length + 1));
  assert(ret);

  if (add_bom)
  {
    *((uint32_t *) ret) = unicode_reverse_codepoint_utf32(0x0000FEFF, reverse);
    ret_top = 4;
  }

  for (size_t k = 0; k < code_points_length; k++)
  {
    *((uint32_t *) &ret[ret_top]) = unicode_reverse_codepoint_utf32(code_points[k], reverse);
    ret_top += 4;
  }
  ret[ret_length] = 0;

  assert(ret_length == ret_top);

  *string_length_ptr = ret_length;
  return ret;
}


unsigned int unicode_code_point_byte_requirement_utf32(uint32_t code_point)
{
  return 4;
}

bool unicode_is_well_formed_utf32(char * string, size_t string_length)
{
  assert(string);
  
  if (string_length == 0)
    return true;
  if (string_length % 4 != 0)
    return false;
  
  uint32_t * data = (uint32_t *) string;
  
  if (data[0] == 0x0000FEFF) /* BOM does not require reversal */
    return unicode_is_well_formed_utf32_imp(&data[1], string_length / 4 - 1, false);
  else if (data[0] == 0xFFFE0000) /* BOM requires reversal */
    return unicode_is_well_formed_utf32_imp(&data[1], string_length / 4 - 1, true);
  else /* NO BOM */
    return 
      unicode_is_well_formed_utf32_imp(data, string_length / 4, true) ||
      unicode_is_well_formed_utf32_imp(data, string_length / 4, false);
}
bool unicode_is_well_formed_utf32be(char * string, size_t string_length)
{
  assert(string);

  return unicode_is_well_formed_utf32_with_endianness(string, string_length, ENDIANNESS_BIG, NULL, NULL);
}
bool unicode_is_well_formed_utf32le(char * string, size_t string_length)
{
  assert(string);
  
  return unicode_is_well_formed_utf32_with_endianness(string, string_length, ENDIANNESS_LITTLE, NULL, NULL);
}

unsigned int unicode_string_length_utf32(char * string, size_t string_length)
{
  assert(string);
  
  bool remove_bom;
  if (
    !unicode_is_well_formed_utf32_with_endianness(string, string_length, ENDIANNESS_LITTLE, NULL, &remove_bom) &&
    !unicode_is_well_formed_utf32_with_endianness(string, string_length, ENDIANNESS_BIG, NULL, &remove_bom)
    )
    assert(0); /* NOT WELL FORMED */
    
  return string_length / 4 - (remove_bom ? 1 : 0);
}
unsigned int unicode_string_length_utf32be(char * string, size_t string_length)
{
  assert(string);
  
  bool remove_bom;
  if (!unicode_is_well_formed_utf32_with_endianness(string, string_length, ENDIANNESS_BIG, NULL, &remove_bom))
    assert(0); /* NOT WELL FORMED */
    
  return string_length / 4 - (remove_bom ? 1 : 0);
}
unsigned int unicode_string_length_utf32le(char * string, size_t string_length)
{
  assert(string);
  
  bool remove_bom;
  if (!unicode_is_well_formed_utf32_with_endianness(string, string_length, ENDIANNESS_LITTLE, NULL, &remove_bom))
    assert(0); /* NOT WELL FORMED */
    
  return string_length / 4 - (remove_bom ? 1 : 0);
}

int unicode_read_utf32be(char * string, uint32_t * code_point)
{
  return unicode_read_utf32_imp(string, code_point, utilities_get_endianness() != ENDIANNESS_BIG);
}
int unicode_read_utf32le(char * string, uint32_t * code_point)
{
  return unicode_read_utf32_imp(string, code_point, utilities_get_endianness() != ENDIANNESS_LITTLE);
}

int unicode_write_utf32(uint32_t code_point, char * string)
{
  return unicode_write_utf32be(code_point, string);
}
int unicode_write_utf32be(uint32_t code_point, char * string)
{
  return unicode_write_utf32_imp(code_point, string, ENDIANNESS_BIG);
}
int unicode_write_utf32le(uint32_t code_point, char * string)
{
  return unicode_write_utf32_imp(code_point, string, ENDIANNESS_LITTLE);
}

uint32_t * unicode_read_string_utf32(char * string, size_t string_length, size_t * code_points_length_ptr)
{
  bool reverse, remove_bom;
  if (
      unicode_is_well_formed_utf32_with_endianness(string, string_length, ENDIANNESS_BIG, &reverse, &remove_bom) || 
      unicode_is_well_formed_utf32_with_endianness(string, string_length, ENDIANNESS_LITTLE, &reverse, &remove_bom)
    )
    return unicode_read_string_utf32_imp(string, string_length, code_points_length_ptr, reverse, remove_bom);
  
  return NULL;
}
uint32_t * unicode_read_string_utf32be(char * string, size_t string_length, size_t * code_points_length_ptr)
{
  bool reverse, remove_bom;
  if (
      unicode_is_well_formed_utf32_with_endianness(string, string_length, ENDIANNESS_BIG, &reverse, &remove_bom)
    )
    return unicode_read_string_utf32_imp(string, string_length, code_points_length_ptr, reverse, remove_bom);
  
  return NULL;
}
uint32_t * unicode_read_string_utf32le(char * string, size_t string_length, size_t * code_points_length_ptr)
{
  bool reverse, remove_bom;
  if (
      unicode_is_well_formed_utf32_with_endianness(string, string_length, ENDIANNESS_LITTLE, &reverse, &remove_bom)
    )
    return unicode_read_string_utf32_imp(string, string_length, code_points_length_ptr, reverse, remove_bom);
  
  return NULL;
}


char * unicode_write_string_utf32(uint32_t * code_points, size_t code_points_length, size_t * string_length_ptr)
{
  return unicode_write_string_utf32be(code_points, code_points_length, string_length_ptr); 
}
char * unicode_write_string_utf32be(uint32_t * code_points, size_t code_points_length, size_t * string_length_ptr)
{
  return unicode_write_string_utf32_imp(code_points, code_points_length, string_length_ptr, utilities_get_endianness() != ENDIANNESS_BIG, true);
}
char * unicode_write_string_utf32le(uint32_t * code_points, size_t code_points_length, size_t * string_length_ptr)
{
  return unicode_write_string_utf32_imp(code_points, code_points_length, string_length_ptr, utilities_get_endianness() != ENDIANNESS_LITTLE, true);
}

char * unicode_write_string_utf32_without_bom(uint32_t * code_points, size_t code_points_length, size_t * string_length_ptr)
{
  return unicode_write_string_utf32be_without_bom(code_points, code_points_length, string_length_ptr); 
}
char * unicode_write_string_utf32be_without_bom(uint32_t * code_points, size_t code_points_length, size_t * string_length_ptr)
{
  return unicode_write_string_utf32_imp(code_points, code_points_length, string_length_ptr, utilities_get_endianness() != ENDIANNESS_BIG, false);
}
char * unicode_write_string_utf32le_without_bom(uint32_t * code_points, size_t code_points_length, size_t * string_length_ptr)
{
  return unicode_write_string_utf32_imp(code_points, code_points_length, string_length_ptr, utilities_get_endianness() != ENDIANNESS_LITTLE, false);
}



