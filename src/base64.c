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
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

#include "mtest.h"
#include "strings.h"
#include "utilities.h"

#include "base64.h"

#define __BASE64_PADDING_CHAR '='
const char __BASE64_VALUE_TO_CHAR_TABLE[] = {
  'A', 'B', 'C', 'D', 'E',
  'F', 'G', 'H', 'I', 'J',
  'K', 'L', 'M', 'N', 'O',
  'P', 'Q', 'R', 'S', 'T',
  'U', 'V', 'W', 'X', 'Y',
  'Z', 'a', 'b', 'c', 'd',
  'e', 'f', 'g', 'h', 'i',
  'j', 'k', 'l', 'm', 'n',
  'o', 'p', 'q', 'r', 's',
  't', 'u', 'v', 'w', 'x',
  'y', 'z', '0', '1', '2',
  '3', '4', '5', '6', '7',
  '8', '9', '+', '/'
};


static char base64_value_to_char(uint8_t value)
{
  value &= 0x3F;
  return __BASE64_VALUE_TO_CHAR_TABLE[value];
}

static uint8_t base64_char_to_value(char c)
{
  if (c >= 'A' && c <= 'Z')
    return (uint8_t) (c - 'A');
  else if (c >= 'a' && c <= 'z')
    return (uint8_t) (c - 'a') + 26;
  else if (c >= '0' && c <= '9')
    return (uint8_t) (c - '0') + 52;
  else if (c == '+')
    return 62;
  else if (c == '/')
    return 63;
  else
    assert(0);
}

static void base64_encode_tuple(uint8_t * from, char * to, size_t remaining_size, bool padding)
{

  uint8_t buffer [4];
  bool set_2 = false, set_3 = false;

  buffer[0] = (from[0] >> 2) & 0x3F;
  buffer[1] = from[0] << 4;
  buffer[2] = 0x0;
  buffer[3] = 0x0;

  switch (remaining_size)
  {

    default:
      buffer[2] |= (from[2] >> 6) & 0x03;
      buffer[3] |= from[2];
      set_3 = true;

    case 2:
      buffer[1] |= (from[1] >> 4) & 0x0F;
      buffer[2] |= from[1] << 2;
      set_2 = true;

    case 1:
      break;

  }

  to[0] = base64_value_to_char(buffer[0]);
  to[1] = base64_value_to_char(buffer[1]);

  if (set_2)
    to[2] = base64_value_to_char(buffer[2]);
  else if (padding)
    to[2] = __BASE64_PADDING_CHAR;

  if (set_3)
    to[3] = base64_value_to_char(buffer[3]);
  else if (padding)
    to[3] = __BASE64_PADDING_CHAR;

}

static void base64_decode_tuple(char * from, uint8_t * to, size_t remaining_size)
{
  uint8_t buffer [4];

  for (unsigned int k = 0; k < remaining_size && k < 4; k++)
  {
    buffer[k] = base64_char_to_value(from[k]);
  }

  to[0] = (buffer[0] << 2) | ((buffer[1] >> 4) & 0x03);

  if (remaining_size >= 3)
    to[1] = (buffer[1] << 4) | ((buffer[2] >> 2) & 0x0F);
  if (remaining_size >= 4)
    to[2] = (buffer[2] << 6) | buffer[3];
}

static unsigned int base64_is_well_formed_imp(char * string, unsigned int string_length)
{

  unsigned int
    string_length_mod,
    scan_length;

  if (string_length == 0)
    return 0;

  string_length_mod = string_length % 4;
  if (string_length_mod == 0)
  {
    if (string[string_length - 1] == __BASE64_PADDING_CHAR)
    {
      if (string[string_length - 2] == __BASE64_PADDING_CHAR)
        scan_length = string_length - 2;
      else
        scan_length = string_length - 1;
    }
    else
      scan_length = string_length;
  }
  else if (string_length_mod == 1)
    return 0;
  else
    scan_length = string_length;

  for (unsigned int k = 0; k < scan_length; k++)
  {
    if (!base64_is_valid_char(string[k]))
      return 0;
  }

  return scan_length;
}

static char * base64_encode_imp(uint8_t * data, size_t data_size, bool padding)
{
  assert(data);
  assert(data_size > 0);

  size_t
    ret_size,
    data_top;
  char
    * ret;

  if (padding)
    ret_size = 4 * (utilities_round_size_upward(data_size, 3) / 3);
  else
    ret_size = utilities_multiply_round_up(data_size, 4.0 / 3.0);

  ret = (char *) _malloc(sizeof(char) * (ret_size + 1));
  assert(ret);

  data_top = 0;
  for (size_t k = 0; k < ret_size; k += 4)
  {
    base64_encode_tuple(&data[data_top], &ret[k], data_size - data_top, padding);
    data_top += 3;
  }

  ret[ret_size] = '\0';
  return ret;
}

static size_t base64_find_decoded_data_size(unsigned int encoded_size)
{
  unsigned int mod = encoded_size % 4;
  if (mod == 0)
    return 3 * (encoded_size / 4);
  else if (mod == 2)
    return 3 * (encoded_size / 4) + 1;
  else if (mod == 3)
    return 3 * (encoded_size / 4) + 2;
  else
    assert(0);
}

bool base64_is_valid_char(char c)
{
  return
    (c >= 'A' && c <= 'Z') ||
    (c >= 'a' && c <= 'z') ||
    (c >= '0' && c <= '9') ||
    (c == '+') ||
    (c == '/');
}



char * base64_encode(uint8_t * data, size_t data_size)
{
  return base64_encode_imp(data, data_size, true);
}

char * base64_encode_non_padded(uint8_t * data, size_t data_size)
{
  return base64_encode_imp(data, data_size, false);
}

uint8_t * base64_decode(char * string, size_t * decoded_size_ptr)
{
  assert(string);

  return base64_decode_up_to(string, strings_length(string), decoded_size_ptr);
}

uint8_t * base64_decode_up_to(char * string, size_t string_length, size_t * decoded_size_ptr)
{
  assert(string);
  assert(decoded_size_ptr);
  assert(string_length > 0);

  unsigned int
    normalized_string_length = base64_is_well_formed_imp(string, string_length);
  assert(normalized_string_length > 0);

  size_t
    ret_size = base64_find_decoded_data_size(normalized_string_length),
    ret_top;
  uint8_t * ret = (uint8_t *) _malloc(sizeof(uint8_t) * ret_size);
  assert(ret);

  ret_top = 0;
  for (size_t k = 0; k < normalized_string_length; k += 4)
  {
    base64_decode_tuple(&string[k], &ret[ret_top], normalized_string_length - k);
    ret_top += 3;
  }

  *decoded_size_ptr = ret_size;
  return ret;
}

bool base64_is_well_formed(char * data)
{
  assert(data);

  return base64_is_well_formed_imp(data, strings_length(data)) > 0;
}

bool base64_is_well_formed_up_to(char * data, size_t length)
{
  assert(data);

  return base64_is_well_formed_imp(data, length);
}
