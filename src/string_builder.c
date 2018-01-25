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
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "mtest.h"
#include "strings.h"
#include "unicode.h"

#include "string_builder.h"

#define STRING_BUILDER_BLOCK_SIZE 1024

char * _string_builder_temp_string = NULL;


struct StringBuilder
{
  char * data;
  unsigned int length;
  unsigned int data_length;
};

/* internal methods */

static void string_builder_resize(StringBuilder * sb, unsigned int addition_size)
{
  if (sb->length + addition_size > sb->data_length)
  {
    unsigned int new_block_count = 1;
    while (sb->length + addition_size > sb->data_length + new_block_count * STRING_BUILDER_BLOCK_SIZE)
    {
      new_block_count++;
    }

    sb->data_length += new_block_count * STRING_BUILDER_BLOCK_SIZE;
    sb->data = (char *) _realloc(sb->data, sb->data_length);
    assert(sb->data);
  }
}

/* end of internal methods */

StringBuilder * string_builder_new()
{
  return string_builder_new_with(STRING_BUILDER_BLOCK_SIZE);
}

StringBuilder * string_builder_new_with(unsigned int size)
{
  assert(size > 0);

  StringBuilder * sb = (StringBuilder *) _malloc(sizeof(StringBuilder));
  assert(sb);

  sb->data = (char *) _malloc(size * sizeof(char));
  assert(sb->data);

  sb->length = 0;
  sb->data_length = size;

  return sb;
}

void string_builder_destroy(StringBuilder * sb)
{
  assert(sb);

  _free(sb->data);
  _free(sb);
}

void string_builder_clear(StringBuilder * sb)
{
  assert(sb);

  sb->length = 0;
}


unsigned int string_builder_length(StringBuilder * sb)
{
  assert(sb);

  return sb->length;
}

void string_builder_append(StringBuilder * sb, char * string)
{
  assert(sb);
  assert(string);

  unsigned int string_length = strings_length(string);

  string_builder_resize(sb, string_length);

  memcpy(
    &sb->data[sb->length],
    string,
    string_length * sizeof(char)
    );

  sb->length += string_length;
}

void string_builder_append_line(StringBuilder * sb)
{
  string_builder_append_char(sb, '\n');
}

void string_builder_append_char(StringBuilder * sb, char c)
{
  assert(sb);
  assert(c); /* cannot add null character */

  string_builder_resize(sb, 1);

  sb->data[sb->length] = c;
  sb->length += 1;
}
void string_builder_append_int(StringBuilder * sb, long long l)
{
  assert(sb);

  char buffer [0xFF];
  sprintf(buffer, "%lld", l);
  unsigned int length = strings_length(buffer);

  string_builder_resize(sb, length);

  memcpy(
    &sb->data[sb->length],
    buffer,
    length * sizeof(char)
    );

  sb->length += length;
}

void string_builder_append_float(StringBuilder * sb, double d)
{
  assert(sb);

  char buffer [0xFF];
  sprintf(buffer, "%f", d);
  unsigned int length = strings_length(buffer);

  string_builder_resize(sb, length);

  memcpy(
    &sb->data[sb->length],
    buffer,
    length * sizeof(char)
    );

  sb->length += length;
}


void string_builder_appendf(StringBuilder * sb, char * format, ...)
{
  assert(sb);
  assert(format);

  va_list args;
  unsigned int length;
  char * string;

  va_start(args, format);
  string = strings_vformat(format, args);
  va_end(args);

  length = strings_length(string);
  string_builder_resize(sb, length);

  memcpy(
    &sb->data[sb->length],
    string,
    length * sizeof(char)
    );

  sb->length += length;

  _free(string);
}

void string_builder_append_code_point(StringBuilder * sb, uint32_t code_point)
{
  assert(sb);
  assert(code_point != 0);
  assert(unicode_is_valid_code_point(code_point));

  char buffer [0x8];
  int length;

  length = unicode_write_utf8(code_point, buffer);
  string_builder_resize(sb, length);

  memcpy(
    &sb->data[sb->length],
    buffer,
    length * sizeof(char)
    );

  sb->length += length;
}


char * string_builder_to_string(StringBuilder * sb)
{
  assert(sb);

  char * ret = (char *) _malloc((sb->length + 1) * sizeof(char));
  assert(ret);

  memcpy(
    ret,
    sb->data,
    sb->length * sizeof(char)
    );
  ret[sb->length] = '\0';

  return ret;
}

char * string_builder_to_temp_string(StringBuilder * sb)
{
  if (_string_builder_temp_string != NULL)
  {
    _free(_string_builder_temp_string);
    _string_builder_temp_string = NULL;
  }

  _string_builder_temp_string = string_builder_to_string(sb);
  return _string_builder_temp_string;
}

char * string_builder_to_string_destroy(StringBuilder * sb)
{
  assert(sb);

  char * ret = string_builder_to_string(sb);
  string_builder_destroy(sb);

  return ret;
}
