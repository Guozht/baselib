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



static int unicode_code_point_byte_header_utf8(char header)
{

  if ((header & 0x80) == 0x0)
    return 1;
  else if ((header & 0xC0) == 0x80)
    return -1;
  else if ((header & 0xE0) == 0xC0)
    return 2;
  else if ((header & 0xF0) == 0xE0)
    return 3;
  else if ((header & 0xF8) == 0xF0)
    return 4;
  else
    return 0;
}

static unsigned int unicode_code_point_string_size_requirement_utf8(uint32_t * code_points, size_t code_points_length)
{
  unsigned int ret = 0, tmp;

  for (size_t k = 0; k < code_points_length; k++)
  {
    tmp = unicode_code_point_byte_requirement_utf8(code_points[k]);
    assert(tmp);
    ret += tmp;
  }

  return ret;
}

static unsigned int unicode_string_length_utf8_imp(char * string, size_t string_length)
{
  unsigned int top = 0, ret = 0;
  while (top < string_length)
  {
    top += unicode_code_point_byte_header_utf8(string[top]);
    ret++;
  }

  return ret;
}


unsigned int unicode_code_point_byte_requirement_utf8(uint32_t code_point)
{
  if (code_point <= 0x7F)
    return 1;
  else if (code_point <= 0x7FF)
    return 2;
  else if (code_point <= 0xFFFF)
    return 3;
  else if (code_point <= 0x10FFFF)
    return 4;
  else
    return 0;
}

bool unicode_is_well_formed_utf8(char * string, size_t string_length)
{
  assert(string);

  unsigned int runner = 0;
  int header;
  for (size_t k = 0; k < string_length; k++)
  {

    if (runner == 0)
    {
      header = unicode_code_point_byte_header_utf8(string[k]);
      if (header <= 0)
        return false;

      runner = header - 1;
    }
    else
    {
      header = unicode_code_point_byte_header_utf8(string[k]);
      if (header != -1)
        return false;

      runner--;
    }
  }

  return runner == 0;
}

unsigned int unicode_string_length_utf8(char * string, size_t string_length)
{
  assert(string);
  assert(unicode_is_well_formed_utf8(string, string_length));

  return unicode_string_length_utf8_imp(string, string_length);
}



int unicode_read_utf8(char * string, uint32_t * code_point)
{
  assert(string);
  assert(code_point);

  int width = unicode_code_point_byte_header_utf8(string[0]);

  switch (width)
  {
    case 1:
      *code_point = string[0];
      break;
    case 2:
      *code_point = ((string[0] & 0x1F) << 6) | (string[1] & 0x3F);
      break;
    case 3:
      *code_point = ((string[0] & 0x0F) << 12) | ((string[1] & 0x3F) << 6) | (string[2] & 0x3F);
      break;
    case 4:
      *code_point = ((string[0] & 0x07) << 18) | ((string[1] & 0x3F) << 12) | ((string[2] & 0x3F) << 6) | (string[3] & 0x3F);
      break;

    default:
      return 0;

  }

  if (unicode_code_point_byte_requirement_utf8(*code_point) == width)
    return width;
  else
    return -width;
}

int unicode_write_utf8(uint32_t code_point, char * string)
{
  int byte_requirement = unicode_code_point_byte_requirement_utf8(code_point);

  if (byte_requirement == 1)
  {
    string[0] = (char) code_point;
  }
  else if (byte_requirement == 2)
  {
    string[0] = (char) (((code_point >> 6) & 0x1F) | 0xC0);
    string[1] = (char) ((code_point & 0x3F) | 0x80);
  }
  else if (byte_requirement == 3)
  {
    string[0] = (char) (((code_point >> 12) & 0x0F) | 0xE0);
    string[1] = (char) (((code_point >> 6) & 0x3F) | 0x80);
    string[2] = (char) ((code_point & 0x3F) | 0x80);
  }
  else if (byte_requirement == 4)
  {
    string[0] = (char) (((code_point >> 18) & 0x07) | 0xF0);
    string[1] = (char) (((code_point >> 12) & 0x3F) | 0x80);
    string[2] = (char) (((code_point >> 6) & 0x3F) | 0x80);
    string[3] = (char) ((code_point & 0x3F) | 0x80);
  }
  else
    return 0;

  return byte_requirement;
}


uint32_t * unicode_read_string_utf8(char * string, size_t string_length, size_t * code_points_length_ptr)
{
  assert(string);
  assert(code_points_length_ptr);

  if (!unicode_is_well_formed_utf8(string, string_length))
    return NULL;

  unsigned int
    utf8_length = unicode_string_length_utf8_imp(string, string_length),
    string_top;
  uint32_t * ret = (uint32_t *) malloc(sizeof(uint32_t) * (utf8_length + 1));
  assert(ret);

  string_top = 0;

  for (unsigned int k = 0; k < utf8_length; k++)
  {
    string_top += unicode_read_utf8(&string[string_top], &ret[k]);
  }
  ret[utf8_length] = 0;

  *code_points_length_ptr = utf8_length;
  return ret;
}

/* expects null terminlated code point list */
char * unicode_write_string_utf8(uint32_t * code_points, size_t code_points_length, size_t * string_length_ptr)
{
  assert(code_points);
  assert(string_length_ptr);

  unsigned int
    string_size = unicode_code_point_string_size_requirement_utf8(code_points, code_points_length),
    string_top;
  char * ret = (char *) malloc(sizeof(char) * (string_size + 1));
  assert(ret);

  string_top = 0;

  for (unsigned int k = 0; k < code_points_length; k++)
  {
    string_top += unicode_write_utf8(code_points[k], &ret[string_top]);
  }

  ret[string_size] = '\0';
  
  *string_length_ptr = string_size;
  return ret;
}


