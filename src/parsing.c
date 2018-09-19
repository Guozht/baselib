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
#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "strings.h"
#include "utilities.h"

#include "parsing.h"


static bool parsing_integer_start_is_correct(char c, bool allow_signed)
{
  return
    (c >= '0' && c <= '9') ||
    (c == '+') ||
    (c == '-' && allow_signed);

}
static bool parsing_ulong_out_of_range(unsigned long value, size_t size)
{
  switch (size)
  {
    case 1:
      return value > 0xFFull;
    case 2:
      return value > 0xFFFFull;
    case 4:
      return value > 0xFFFFFFFFull;
    case 8:
      return false;
    default:
      assert(0);
  }
}

static bool parsing_long_out_of_range(long value, size_t size, bool is_signed)
{
  if (!is_signed)
    return parsing_ulong_out_of_range((unsigned long) value, size);

  switch (size)
  {
    case 1:
      return value > 0x7Fll || value < -1 * 0x80ll;
    case 2:
      return value > 0x7FFFll || value < -1 * 0x8000ll;
    case 4:
      return value > 0x7FFFFFFFll || value < -1 * 0x80000000ll;
    case 8:
      return false;
    default:
      assert(0);
  }
}

static bool parsing_ulong_long_out_of_range(
    unsigned long long value, 
    size_t size
    )
{
  switch (size)
  {
    case 1:
      return value > 0xFFull;
    case 2:
      return value > 0xFFFFull;
    case 4:
      return value > 0xFFFFFFFFull;
    case 8:
      return false;
    default:
      assert(0);
  }
}
static bool parsing_long_long_out_of_range(
    long long value, 
    size_t size, 
    bool is_signed
    )
{
  if (!is_signed)
    return parsing_ulong_long_out_of_range((unsigned long long) value, size);

  switch (size)
  {
    case 1:
      return value > 0x7Fll || value < -1 * 0x80ll;
    case 2:
      return value > 0x7FFFll || value < -1 * 0x8000ll;
    case 4:
      return value > 0x7FFFFFFFll || value < -1 * 0x80000000ll;
    case 8:
      return false;
    default:
      assert(0);
  }
}
static bool try_parse_small_int_imp(
    char * str,
    void * ptr,
    size_t size,
    bool is_signed
    )
{
  long value;
  long (*callback)(const char *, char **, int);
  char * endptr;
  
  if (!parsing_integer_start_is_correct(str[0], is_signed))
    return false;

  if (is_signed)
    callback = strtol;
  else
    callback = (long (*)(const char *, char **, int)) strtoul;

  errno = 0;
  value = callback(str, &endptr, 10);
  if (errno == ERANGE)
    return false;
  if (endptr[0])
    return false;
  if (parsing_long_out_of_range(value, size, is_signed))
    return false;

  if (!ptr)
    return true;
  
  switch (endianness_system())
  {
    case ENDIANNESS_BIG:
      memcpy(ptr, &value + sizeof(long) - size, size);
      break;
    case ENDIANNESS_LITTLE:
      memcpy(ptr, &value, size);
      break;
    default:
      assert(0);
  }

  return true;
}

static bool try_parse_big_int_imp(
    char * str,
    void * ptr,
    size_t size,
    bool is_signed
    )
{
  long long value;
  long long (*callback)(const char *, char **, int);
  char * endptr;
  
  if (!parsing_integer_start_is_correct(str[0], is_signed))
    return false;

  if (is_signed)
    callback = strtoll;
  else
    callback = (long long (*)(const char *, char **, int)) strtoull;

  errno = 0;
  value = callback(str, &endptr, 10);
  if (errno == ERANGE)
    return false;
  if (endptr[0])
    return false;
  if (parsing_long_long_out_of_range(value, size, is_signed))
    return false;
 
  if (!ptr)
    return true; 

  switch (endianness_system())
  {
    case ENDIANNESS_BIG:
      memcpy(ptr, &value + sizeof(long long) - size, size);
      break;
    case ENDIANNESS_LITTLE:
      memcpy(ptr, &value, size);
      break;
    default:
      assert(0);
  }

  return true;
}

static bool try_parse_int_imp(
    char * str, 
    void * ptr, 
    size_t size, 
    bool is_signed
    )
{
  if (strings_is_null_or_whitespace(str))
    return false;

  if (size > sizeof(long))
    return try_parse_big_int_imp(str, ptr, size, is_signed);
  else
    return try_parse_small_int_imp(str, ptr, size, is_signed);
}


bool try_parse_short(char * str, short * value_ptr)
{
  return try_parse_int_imp(str, (void *) value_ptr, sizeof(short), true);
}
bool try_parse_int(char * str, int * value_ptr)
{
  return try_parse_int_imp(str, (void *) value_ptr, sizeof(int), true);
}
bool try_parse_long(char * str, long * value_ptr)
{
  return try_parse_int_imp(str, (void *) value_ptr, sizeof(long), true);
}
bool try_parse_long_long(char * str, long long * value_ptr)
{
  return try_parse_int_imp(str, (void *) value_ptr, sizeof(long long), true);
}

bool try_parse_ushort(char * str, unsigned short * value_ptr)
{
  return try_parse_int_imp(
      str, (void *) value_ptr, sizeof(unsigned short), false
      );
}
bool try_parse_uint(char * str, unsigned int * value_ptr)
{
  return try_parse_int_imp(str, (void *) value_ptr, sizeof(unsigned int), false);
}
bool try_parse_ulong(char * str, unsigned long * value_ptr)
{
  return try_parse_int_imp(
      str, (void *) value_ptr, sizeof(unsigned long), false
      );
}
bool try_parse_ulong_long(char * str, unsigned long long * value_ptr)
{
  return try_parse_int_imp(
      str, (void *) value_ptr, sizeof(unsigned long long), false
      );
}

bool try_parse_int8(char * str, int8_t * value_ptr)
{
  return try_parse_int_imp(str, (void *) value_ptr, sizeof(int8_t), true);
}
bool try_parse_uint8(char * str, uint8_t * value_ptr)
{
  return try_parse_int_imp(str, (void *) value_ptr, sizeof(uint8_t), false);
}
bool try_parse_int16(char * str, int16_t * value_ptr)
{
  return try_parse_int_imp(str, (void *) value_ptr, sizeof(int16_t), true);
}
bool try_parse_uint16(char * str, uint16_t * value_ptr)
{
  return try_parse_int_imp(str, (void *) value_ptr, sizeof(uint16_t), false);
}
bool try_parse_int32(char * str, int32_t * value_ptr)
{
  return try_parse_int_imp(str, (void *) value_ptr, sizeof(int32_t), true);
}
bool try_parse_uint32(char * str, uint32_t * value_ptr)
{
  return try_parse_int_imp(str, (void *) value_ptr, sizeof(uint32_t), false);
}
bool try_parse_int64(char * str, int64_t * value_ptr)
{
  return try_parse_int_imp(str, (void *) value_ptr, sizeof(int64_t), true);
}
bool try_parse_uint64(char * str, uint64_t * value_ptr)
{
  return try_parse_int_imp(str, (void *) value_ptr, sizeof(uint64_t), false);
}

