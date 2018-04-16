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
#include <stdio.h> /* for size_t */
#include <stdlib.h>
#include <string.h>

#include "base64.h"
#include "mtest.h"
#include "string_builder.h"
#include "strings.h"
#include "unicode.h"
#include "utilities.h"

static bool unicode_utf7_is_direct_char(uint32_t c)
{
  if (c == '\n' || c == '\r')
    return true;
  return
    c >= 0x20 && c < 0x7F &&
    c != (uint32_t) '+' &&
    c != (uint32_t) '~' &&
    c != (uint32_t) '\\';
}

static bool unicode_utf7_base64_represents_valid_codepoints(char * base64)
{
  if (!base64_is_well_formed(base64))
    return false;

  size_t data_length, utf16_data_length;
  char * data;
  uint32_t * utf16_data;
  bool valid = true;

  data = base64_decode(base64, &data_length);
  if (!unicode_is_well_formed_utf16be((char *) data, data_length))
  {
    _free(data);
    return false;
  }

  utf16_data = unicode_read_string_utf16((char *) data, data_length, &utf16_data_length);
  for (size_t k = 0; k < utf16_data_length && valid; k++)
  {
    if (!unicode_is_valid_code_point(utf16_data[k]))
      valid = false;
  }

  _free(data);
  _free(utf16_data);

  return data;
}


static void unicode_parse_base64_to_code_points(char * string, uint32_t * code_points, size_t * code_points_length_ptr)
{
  size_t data_length, utf16_code_points_length;
  uint32_t * utf16_code_points;
  char * data;

  data = base64_decode(string, &data_length);

  utf16_code_points = unicode_read_string_utf16be((char *) data, data_length, &utf16_code_points_length);

  memcpy(&code_points[*code_points_length_ptr], utf16_code_points, sizeof(uint32_t) * utf16_code_points_length);
  *code_points_length_ptr += utf16_code_points_length;

  _free(utf16_code_points);
  _free(data);
}

static size_t unicode_get_string_length_of_base64(char * string)
{
  size_t data_length, ret;
  char * data;

  data = base64_decode(string, &data_length);
  ret = unicode_string_length_utf16be((char *) data, data_length);
  _free(data);

  return ret;
}

unsigned int unicode_code_point_byte_requirement_utf7(uint32_t code_point)
{
  if (unicode_utf7_is_direct_char(code_point))
    return 1;
  return 2 + utilities_multiply_round_up(
      unicode_code_point_byte_requirement_utf16(code_point), 
      4.0 / 3.0
    );
}
bool unicode_is_well_formed_utf7(char * string, size_t string_length)
{
  assert(string);
  assert(string_length > 0);

  StringBuilder * sb = string_builder_new();
  bool
    in_base64 = false,
    last_was_plus = false,
    valid = true;
  char
    c,
    * base64_string;

  for (unsigned int k = 0; k < string_length && valid; k++)
  {
    c = string[k];

    if (in_base64)
    {
      if (base64_is_valid_char(c))
        string_builder_append_char(sb, c);
      else
      {
        base64_string = string_builder_to_string(sb);
        string_builder_clear(sb);
        if (!unicode_utf7_base64_represents_valid_codepoints(base64_string))
          valid = false;
        _free(base64_string);

        k--; /* reparse last character */
        in_base64 = false;
      }
    }
    else if (last_was_plus)
    {
      last_was_plus = false;
      
      if (base64_is_valid_char(c))
      {
        in_base64 = true;
        string_builder_append_char(sb, c);
      }
      else if (c != '-')
        valid = false;
    }
    else
    {
      if ((c >= 0x20 && c <= 0x7F) || c == '\n' || c == '\r' || c == '\t')
      {
        switch (c)
        {
          case '~':
          case '\\':
            valid = false;
            break;
          case '+':
            last_was_plus = true;
            break;
          default:
            break;
        }
      }
      else
        valid = false;
    }
  }

  string_builder_destroy(sb);

  return valid;
}

unsigned int unicode_string_length_utf7(char * string, size_t string_length)
{
  assert(string);
  assert(string_length > 0);
  assert(unicode_is_well_formed_utf7(string, string_length));
  
  size_t ret = 0, base64_start = 0;
  unsigned char c;
  char * str;
  StringBuilder * sb = string_builder_new();

  for (size_t k = 0; k < string_length; k++)
  {
    c = (unsigned char) string[k];

    if (base64_start != 0)
    {
      if (c == '-')
      {
        if (k == base64_start)
          ret++;
        else
        {
          str = string_builder_to_string(sb);
          string_builder_clear(sb);
          ret += unicode_get_string_length_of_base64(str);
          _free(str);
        }
        base64_start = 0;
      }
      else if (!base64_is_valid_char((char) c))
      {
        str = string_builder_to_string(sb);
        string_builder_clear(sb);
        ret += unicode_get_string_length_of_base64(str);
        _free(str);
        base64_start = 0;
        k--; /* backs up to re-process character */
      }
      else
        string_builder_append_char(sb, (char) c);
    }
    else
    {
      if (c == '+')
        base64_start = k + 1;
      else if (unicode_utf7_is_direct_char(c))
        ret++;
      else
        assert(0);
    }
  }

  if (string_builder_length(sb) != 0)
  {
    str = string_builder_to_string(sb);
    ret += unicode_get_string_length_of_base64(str);
    _free(str);
  }

  string_builder_destroy(sb);

  return ret;
}

int unicode_read_utf7(char * string, uint32_t * code_point)
{
  assert(string);
  assert(code_point);

  size_t k, data_length, utf16_data_length;
  char * data;
  uint32_t * utf16_data;

  if ((string[0] < 0x20 && string[0] != '\n' && string[0] != '\r') || string[0] > 0x7F)
    return 0;
  else if (string[0] == '+')
  {
    for (k = 1; base64_is_valid_char(string[k]); k++)
    {
    }
    
    if (k == 1)
    {
      if (string[1] == '-')
      {
        code_point[0] = (uint32_t) '+';
        return 2;
      }
      else
        return 0;
    }

    if (!base64_is_well_formed_up_to(&string[1], (unsigned int) k - 1))
      return 0;

    data = (char *) base64_decode_up_to(&string[1], k - 1, &data_length);
    if (!unicode_is_well_formed_utf16be((char *) data, data_length))
    {
      _free(data);
      return 0;
    }
    utf16_data = unicode_read_string_utf16be((char *) data, data_length, &utf16_data_length);
    _free(data);

    if (utf16_data_length != 1)
      _free(utf16_data);

    code_point[0] = utf16_data[0];
    _free(utf16_data);

    return (int) k - 1;
  }
  else
  {
    code_point[0] = (uint32_t) string[0];
    return 1;
  } 
}
int unicode_write_utf7(uint32_t code_point, char * string)
{
  assert(string);
  assert(unicode_is_valid_code_point(code_point));

  size_t data_length;
  char * data = unicode_write_string_utf7(&code_point, 1, &data_length);

  memcpy(string, data, data_length);
  _free(data);

  return (int) data_length;
}

uint32_t * unicode_read_string_utf7(char * string, size_t string_length, size_t * code_points_length_ptr)
{
  assert(string);
  assert(string_length > 0);
  assert(code_points_length_ptr);
  assert(unicode_is_well_formed_utf7(string, string_length));
  
  size_t code_points_length = 0, base64_start = 0;
  unsigned char c;
  char * str;
  StringBuilder * sb = string_builder_new();
  uint32_t * code_points = (uint32_t *) _malloc(sizeof(uint32_t) * string_length);
  assert(code_points);

  for (size_t k = 0; k < string_length; k++)
  {
    c = (unsigned char) string[k];

    if (base64_start != 0)
    {
      if (c == '-')
      {
        if (k == base64_start)
          code_points[code_points_length++] = (uint32_t) '+';
        else
        {
          str = string_builder_to_string(sb);
          string_builder_clear(sb);
          unicode_parse_base64_to_code_points(str, code_points, &code_points_length);
          _free(str);
        }
        base64_start = 0;
      }
      else if (!base64_is_valid_char((char) c))
      {
        str = string_builder_to_string(sb);
        string_builder_clear(sb);
        unicode_parse_base64_to_code_points(str, code_points, &code_points_length);
        _free(str);
        base64_start = 0;
        k--; /* backs up to re-process character */
      }
      else
        string_builder_append_char(sb, (char) c);
    }
    else
    {
      if (c == '+')
        base64_start = k + 1;
      else if (unicode_utf7_is_direct_char(c))
        code_points[code_points_length++] = (uint32_t) c;
      else
        assert(0);
    }
  }

  if (string_builder_length(sb) != 0)
  {
    str = string_builder_to_string(sb);
    unicode_parse_base64_to_code_points(str, code_points, &code_points_length);
    _free(str);
  }

  string_builder_destroy(sb);

  *code_points_length_ptr = code_points_length;
  return code_points;
}
char * unicode_write_string_utf7(uint32_t * code_points, size_t code_points_length, size_t * string_length_ptr)
{
  assert(code_points);
  assert(code_points_length > 0);

  StringBuilder * sb = string_builder_new();
  ssize_t base64_start = -1;
  size_t utf16_data_length;
  char * ret, * utf16_data, * base64_str;
  uint32_t c;

  for (size_t k = 0; k < code_points_length; k++)
  {
    c = code_points[k];
    if (base64_start == -1)
    {
      if (unicode_utf7_is_direct_char(c))
        string_builder_append_char(sb, c);
      else if (c == (uint32_t) '+')
        string_builder_append(sb, "+-");
      else {
        base64_start = (ssize_t) k;
        k--;
      }
    }
    else
    {
      if (unicode_utf7_is_direct_char(c))
      {
        utf16_data = unicode_write_string_utf16be_without_bom(&code_points[base64_start], k - base64_start, &utf16_data_length);
        base64_str = base64_encode_non_padded((char *) utf16_data, utf16_data_length); 

        string_builder_appendf(sb, "+%s", base64_str);
        if (!base64_is_valid_char((char) c) && (char) c != '-')
          string_builder_append_char(sb, c);
        else
          string_builder_appendf(sb, "-%c", (char) c);

        _free(base64_str);
        _free(utf16_data);

        base64_start = -1;
      }
    }
  }


  if (base64_start != -1)
  {
    utf16_data = unicode_write_string_utf16be(&code_points[base64_start], code_points_length - base64_start, &utf16_data_length);
    base64_str = base64_encode_non_padded((char *) utf16_data, utf16_data_length); 

    string_builder_appendf(sb, "+%s-", base64_str);

    _free(base64_str);
    _free(utf16_data);
  }

  ret = string_builder_to_string_destroy(sb);
  if (string_length_ptr)
    *string_length_ptr = (size_t) strings_length(ret);


  return ret;
}




