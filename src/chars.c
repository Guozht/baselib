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


#include <stdbool.h>

#include "chars.h"


bool chars_equals(char c1, char c2)
{
  return c1 == c2;
}
bool chars_equals_ignore_case(char c1, char c2)
{
  return chars_to_lower(c1) == chars_to_lower(c2);
}


bool chars_is_lower(char c)
{
  return 'a' <= c && c <= 'z';
}
bool chars_is_upper(char c)
{
  return 'A' <= c && c <= 'Z';
}

bool chars_is_alpha(char c)
{
  return chars_is_lower(c) || chars_is_upper(c);
}
bool chars_is_digit(char c)
{
  return '0' <= c && c <= '9';
}
bool chars_is_alpha_or_digit(char c)
{
  return chars_is_alpha(c) || chars_is_digit(c);
}
bool chars_is_octal_digit(char c)
{
  return '0' <= c && c <= '7';
}
bool chars_is_hex_digit(char c)
{
  return
    chars_is_digit(c) ||
    ('A' <= c && c <= 'F') ||
    ('a' <= c && c <= 'f')
    ;
}
bool chars_is_ascii7(char c)
{
  return (c & 0x7F) == 0;
}


bool chars_is_white_space(char c)
{
  return c <= 0x20;
}

char chars_to_lower(char c)
{
  if (chars_is_upper(c))
    return c + ('a' - 'A');
  else
    return c;
}
char chars_to_upper(char c)
{
  if (chars_is_lower(c))
    return c - ('a' - 'A');
  else
    return c;
}



int chars_order(char c1, char c2)
{
  if (c1 > c2)
    return -1;
  else if (c1 < c2)
    return 1;
  else
    return 0;
}

int chars_order_ignore_case(char c1, char c2)
{
  c1 = chars_to_upper(c1);
  c2 = chars_to_upper(c2);
  if (c1 > c2)
    return -1;
  else if (c1 < c2)
    return 1;
  else
    return 0;
}
