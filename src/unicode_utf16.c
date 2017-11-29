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




static uint16_t unicode_reverse_byte_order_utf16(uint16_t value, bool reverse)
{
  if (reverse)
    return ((value << 8) & 0xFF00) | ((value >> 8) & 0x00FF);
  else
    return value;
}

static bool unicode_is_high_surrogate_utf16(uint16_t value)
{
  return (value & 0xFC00) == 0xD800;
}

static bool unicode_is_low_surrogate_utf16(uint16_t value)
{
  return (value & 0xFC00) == 0xDC00;
}

static bool unicode_determine_endianess_utf16(uint16_t value, bool * reverse)
{
  if (value == 0xFEFF)
  {
    if (reverse)
      *reverse = false;
    return true;
  }
  else if (value == 0xFFFE)
  {
    if (reverse)
      *reverse = true;
    return true;
  }
  else
  {
    if (reverse)
      *reverse = false;
    return false;
  }
}

static Endianness unicode_determine_specified_endianness_utf16(
  uint16_t value,
  Endianness specified,
  bool * under_determined,
  bool * point_removable)
{
  Endianness system_endianness = utilities_get_endianness();

  *under_determined = false;
  *point_removable = false;

  bool reverse;
  if (specified)
  {
    if (unicode_determine_endianess_utf16(value, &reverse))
    {
      if (
        (reverse && specified == system_endianness) ||
        (!reverse && specified != system_endianness)
        )
        return ENDIANNESS_NONE;
      else
      {
        *point_removable = true;
        return specified;
      }
    }
    else
      return specified;
  }
  else
  {
    if (unicode_determine_endianess_utf16(value, &reverse))
    {
      *point_removable = true;
      if (reverse)
        return endianness_flip(system_endianness);
      else
        return system_endianness;
    }
    else
    {
      *under_determined = true;
      return system_endianness;
    }
  }

}

static unsigned int unicode_string_length_utf16_imp(char * string, size_t string_length, Endianness endianness)
{
  unsigned int
    ret;
  uint16_t * data = (uint16_t *) string;

  if (string_length == 0)
    return 0;

  bool
    endian_reverse,
    endianness_under_determined,
    point_removable;

  endianness = unicode_determine_specified_endianness_utf16(*(uint16_t *) string, endianness, &endianness_under_determined, &point_removable);

  if (endianness_under_determined)
  {
    if (unicode_is_well_formed_utf16be(string, string_length))
      endian_reverse = utilities_get_endianness() != ENDIANNESS_BIG;
    else /* string already determined to be well formed, so must be LE */
      endian_reverse = utilities_get_endianness() != ENDIANNESS_LITTLE;
  }
  else
    endian_reverse = endianness != utilities_get_endianness();

  string_length /= 2;
  
  if (point_removable)
  {
    data = &data[1];
    string_length -= 1;
  }
  

  ret = 0;
  for (unsigned int k = 0; k < string_length; k++)
  {
    if (unicode_is_high_surrogate_utf16(unicode_reverse_byte_order_utf16(data[k], endian_reverse)))
      k++;
    
    ret++;
  }
  
  return ret;
}

static int unicode_read_utf16_with_endianness(char * string, uint32_t * code_point, bool system_endianness)
{
  uint16_t first = unicode_reverse_byte_order_utf16(*(uint16_t *)string, !system_endianness);

  if (unicode_is_high_surrogate_utf16(first))
  {
    /* parse double length */
    uint16_t second = unicode_reverse_byte_order_utf16(*(uint16_t *)&string[2], !system_endianness);

    if (!unicode_is_low_surrogate_utf16(second))
      return 0;

    *code_point = ((((uint32_t) first & 0x3FF) << 10) | ((uint32_t) second & 0x3FF)) + 0x10000;
    return 4;
  }
  else
  {
    /* parse single length */

    *code_point = first;
    return 2;
  }

}

static int unicode_write_utf16_with_endianness(uint32_t code_point, char * string, bool system_endianness)
{
  if (code_point <= 0xFFFF)
  {
    *((uint16_t *) string) = unicode_reverse_byte_order_utf16(code_point, !system_endianness);
    return 2;
  }
  else
  {
    uint32_t de_aug = code_point - 0x10000;

    *((uint16_t *) string) = unicode_reverse_byte_order_utf16(
          (((uint16_t) (de_aug >> 10)) & 0x3FF) | 0xD800,
          !system_endianness
          );
    *((uint16_t *) &string[2]) = unicode_reverse_byte_order_utf16(
          (((uint16_t) de_aug) & 0x3FF) | 0xDC00,
          !system_endianness
          );

    return 4;
  }
}



static bool unicode_is_well_formed_utf16_with_endianness(char * string, unsigned int data_length, Endianness endianness)
{
  assert(string);

  if (data_length == 0)
    return true;
  if (data_length % 2 != 0)
    return false;

  data_length /= 2;
  uint32_t
    code_point;
  uint16_t
    * data = (uint16_t *) string,
    value,
    value2;
  bool endian_reverse = utilities_get_endianness() != endianness;

  
  for (unsigned int k = 0; k < data_length; k++)
  {
    value = unicode_reverse_byte_order_utf16(data[k], endian_reverse);
    if (unicode_is_high_surrogate_utf16(value))
    {
      if (k + 1 == data_length)
        return false;
      k++;

      value2 = unicode_reverse_byte_order_utf16(data[k], endian_reverse);
      if (!unicode_is_low_surrogate_utf16(value2))
        return false;
    
      code_point = (((uint32_t) value & 0x03FF) << 10) | ((uint32_t) value2 & 0x03FF);
      code_point += 0x10000;
    }
    else
      code_point = value;
    
    if (!unicode_is_valid_code_point(code_point))
      return false;
    
  }
  return true;
}


static uint32_t * unicode_read_string_utf16_imp(char * string, size_t string_length, size_t * code_points_length_ptr, Endianness endianness)
{
  assert(string);

  if (!unicode_is_well_formed_utf16(string, string_length))
    return NULL;

  unsigned int
    utf16_length = unicode_string_length_utf16_imp(string, string_length, endianness),
    string_top;
  uint32_t
    * ret;
  bool
    reverse,
    endianness_under_determined,
    point_removable;

  if (string_length == 0)
    return NULL;

  endianness = unicode_determine_specified_endianness_utf16(*(uint16_t *) string, endianness, &endianness_under_determined, &point_removable);
  if (!endianness)
    return NULL;

  if (endianness_under_determined)
  {
    if (unicode_is_well_formed_utf16be(string, string_length))
      reverse = utilities_get_endianness() != ENDIANNESS_BIG;
    else /* string already determined to be well formed, so must be LE */
      reverse = utilities_get_endianness() != ENDIANNESS_LITTLE;
  }
  else
    reverse = endianness != utilities_get_endianness();

  if (point_removable)
  {
    string = &string[2];
    string_length -= 2;
  }

  ret = (uint32_t *) malloc(sizeof(uint32_t) * (utf16_length + 1));
  string_top = 0;
  
  for (unsigned int k = 0; k < utf16_length; k++)
  {
    string_top += unicode_read_utf16_with_endianness(&string[string_top], &ret[k], !reverse);
    assert(unicode_is_valid_code_point(ret[k]));
  }
  ret[utf16_length] = 0;

  *code_points_length_ptr = utf16_length;
  return ret;
}

static unsigned int unicode_code_point_byte_requirement_for_string_utf16(uint32_t * code_points, size_t code_points_length)
{
  unsigned int ret = 0;

  for (size_t k = 0; k < code_points_length; k++)
  {
    ret += unicode_code_point_byte_requirement_utf16(code_points[k]);
  }

  return ret;
}

static char * unicode_write_string_utf16_imp(uint32_t * code_points, size_t code_points_length, size_t * strings_length_ptr, bool reverse, bool include_bom)
{
  assert(code_points);

  unsigned int
    string_length = unicode_code_point_byte_requirement_for_string_utf16(code_points, code_points_length),
    string_top;

  if (include_bom)
  {
    string_length += 2;
    string_top = 2;
  }
  else
    string_top = 0;

  char
    * ret = (char *) malloc(sizeof(char) * (string_length + 1));

  if (include_bom)
    *((uint64_t *) ret) = unicode_reverse_byte_order_utf16(0xFEFF, reverse);

  for (unsigned int k = 0; k < code_points_length; k++)
  {
    string_top += unicode_write_utf16_with_endianness(code_points[k], &ret[string_top], !reverse);
  }

  *strings_length_ptr = string_length;
  return ret;
}




unsigned int unicode_code_point_byte_requirement_utf16(uint32_t code_point)
{
  if (code_point <= 0xFFFF)
    return 2;
  else
    return 4;
}

bool unicode_is_well_formed_utf16(char * string, size_t string_length)
{
  assert(string);

  if (string_length == 0)
    return true;
  if (string_length == 1)
    return false;

  uint16_t * data = (uint16_t *) string;
  bool endian_reverse;

  if (unicode_determine_endianess_utf16(data[0], &endian_reverse))
  {
    Endianness system_endianness = utilities_get_endianness();
    return unicode_is_well_formed_utf16_with_endianness(
      &string[2],
      string_length - 2,
      endian_reverse ? endianness_flip(system_endianness) : system_endianness
      );
  }
  else
  {
    return
      unicode_is_well_formed_utf16_with_endianness(string, string_length, ENDIANNESS_BIG) ||
      unicode_is_well_formed_utf16_with_endianness(string, string_length, ENDIANNESS_LITTLE);
  }
}



bool unicode_is_well_formed_utf16be(char * string, size_t string_length)
{
  assert(string);
  return unicode_is_well_formed_utf16_with_endianness(string, string_length, ENDIANNESS_BIG);
}

bool unicode_is_well_formed_utf16le(char * string, size_t string_length)
{
  assert(string);
  return unicode_is_well_formed_utf16_with_endianness(string, string_length, ENDIANNESS_LITTLE);
}

unsigned int unicode_string_length_utf16(char * string, size_t string_length)
{
  assert(string);
  assert(unicode_is_well_formed_utf16(string, string_length));

  return unicode_string_length_utf16_imp(string, string_length, ENDIANNESS_NONE);
}
unsigned int unicode_string_length_utf16be(char * string, size_t string_length)
{
  assert(string);
  assert(unicode_is_well_formed_utf16(string, string_length));

  return unicode_string_length_utf16_imp(string, string_length, ENDIANNESS_NONE);
}
unsigned int unicode_string_length_utf16le(char * string, size_t string_length)
{
  assert(string);
  assert(unicode_is_well_formed_utf16(string, string_length));

  return unicode_string_length_utf16_imp(string, string_length, ENDIANNESS_NONE);
}


int unicode_read_utf16be(char * string, uint32_t * code_point)
{
  return unicode_read_utf16_with_endianness(string, code_point, utilities_get_endianness() == ENDIANNESS_BIG);
}
int unicode_read_utf16le(char * string, uint32_t * code_point)
{
  return unicode_read_utf16_with_endianness(string, code_point, utilities_get_endianness() == ENDIANNESS_LITTLE);
}

int unicode_write_utf16(uint32_t code_point, char * string)
{
  assert(unicode_is_valid_code_point(code_point));
  assert(string);

  return unicode_write_utf16_with_endianness(code_point, string, true); /* system endianness */
}

int unicode_write_utf16be(uint32_t code_point, char * string)
{
  assert(unicode_is_valid_code_point(code_point));
  assert(string);

  return unicode_write_utf16_with_endianness(code_point, string, utilities_get_endianness() == ENDIANNESS_BIG);
}
int unicode_write_utf16le(uint32_t code_point, char * string)
{
  assert(unicode_is_valid_code_point(code_point));
  assert(string);

  return unicode_write_utf16_with_endianness(code_point, string, utilities_get_endianness() == ENDIANNESS_LITTLE);
}

uint32_t * unicode_read_string_utf16(char * string, size_t string_length, size_t * code_points_length_ptr)
{
  return unicode_read_string_utf16_imp(string, string_length, code_points_length_ptr, ENDIANNESS_NONE);
}
uint32_t * unicode_read_string_utf16be(char * string, size_t string_length, size_t * code_points_length_ptr)
{
  return unicode_read_string_utf16_imp(string, string_length, code_points_length_ptr, ENDIANNESS_BIG);
}
uint32_t * unicode_read_string_utf16le(char * string, size_t string_length, size_t * code_points_length_ptr)
{
  return unicode_read_string_utf16_imp(string, string_length, code_points_length_ptr, ENDIANNESS_LITTLE);
}

char * unicode_write_string_utf16(uint32_t * code_points, size_t code_points_length, size_t * string_length_ptr)
{
  return unicode_write_string_utf16_imp(code_points, code_points_length, string_length_ptr, false, true);
}
char * unicode_write_string_utf16be(uint32_t * code_points, size_t code_points_length, size_t * string_length_ptr)
{
  return unicode_write_string_utf16_imp(code_points, code_points_length, string_length_ptr, utilities_get_endianness() != ENDIANNESS_BIG, true);
}
char * unicode_write_string_utf16le(uint32_t * code_points, size_t code_points_length, size_t * string_length_ptr)
{
  return unicode_write_string_utf16_imp(code_points, code_points_length, string_length_ptr, utilities_get_endianness() != ENDIANNESS_LITTLE, true);
}


char * unicode_write_string_utf16_without_bom(uint32_t * code_points, size_t code_points_length, size_t * string_length_ptr)
{
  return unicode_write_string_utf16_imp(code_points, code_points_length, string_length_ptr, false, false);
}

char * unicode_write_string_utf16be_without_bom(uint32_t * code_points, size_t code_points_length, size_t * string_length_ptr)
{
  return unicode_write_string_utf16_imp(code_points, code_points_length, string_length_ptr, utilities_get_endianness() != ENDIANNESS_BIG, false);
}

char * unicode_write_string_utf16le_without_bom(uint32_t * code_points, size_t code_points_length, size_t * string_length_ptr)
{
  return unicode_write_string_utf16_imp(code_points, code_points_length, string_length_ptr, utilities_get_endianness() != ENDIANNESS_LITTLE, false);
}


