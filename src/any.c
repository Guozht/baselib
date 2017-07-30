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

#include "any.h"

#include <assert.h>


Any char_to_any(char c)
{
  return (Any) {
    ANY_TYPE_CHAR,
    (union _Any) c
  };
}
Any schar_to_any(signed char c)
{
  return (Any) {
    ANY_TYPE_SCHAR,
    (union _Any) c
  };
}
Any uchar_to_any(unsigned char c)
{
  return (Any) {
    ANY_TYPE_UCHAR,
    (union _Any) c
  };
}

Any short_to_any(short s)
{
  return (Any) {
    ANY_TYPE_SHORT,
    (union _Any) s
  };
}
Any ushort_to_any(unsigned short s)
{
  return (Any) {
    ANY_TYPE_USHORT,
    (union _Any) s
  };
}

Any int_to_any(int i)
{
  return (Any) {
    ANY_TYPE_INT,
    (union _Any) i
  };
}
Any uint_to_any(unsigned int i)
{
  return (Any) {
    ANY_TYPE_UINT,
    (union _Any) i
  };
}

Any long_to_any(long l)
{
  return (Any) {
    ANY_TYPE_LONG,
    (union _Any) l
  };
}
Any ulong_to_any(unsigned int l)
{
  return (Any) {
    ANY_TYPE_ULONG,
    (union _Any) l
  };
}

Any long_long_to_any(long l)
{
  return (Any) {
    ANY_TYPE_LONGLONG,
    (union _Any) l
  };
}
Any ulong_long_to_any(long l)
{
  return (Any) {
    ANY_TYPE_ULONGLONG,
    (union _Any) l
  };
}

Any float_to_any(float f)
{
  return (Any) {
    ANY_TYPE_FLOAT,
    (union _Any) f
  };
}
Any double_to_any(double d)
{
  return (Any) {
    ANY_TYPE_DOUBLE,
    (union _Any) d
  };
}

Any bool_to_any(bool b)
{
  return (Any) {
    ANY_TYPE_BOOL,
    (union _Any) b
  };
}

Any void_to_any(void * v)
{
  return (Any) {
    ANY_TYPE_POINTER,
    (union _Any) v
  };
}
Any ptr_to_any(void * v)
{
  return void_to_any(v);
}
Any pointer_to_any(void * v)
{
  return void_to_any(v);
}

Any string_to_any(char * str)
{
  return (Any) {
    ANY_TYPE_STRING,
    (union _Any) str
  };
}
Any str_to_any(char * str)
{
  return string_to_any(str);
}



char any_to_char(Any a)
{
  assert(a.type == ANY_TYPE_CHAR);
  return a.value._char;
}
signed char any_to_schar(Any a)
{
  assert(a.type == ANY_TYPE_SCHAR);
  return a.value._signed_char;
}
unsigned char any_to_uchar(Any a)
{
  assert(a.type == ANY_TYPE_UCHAR);
  return a.value._unsigned_char;
}

short any_to_short(Any a)
{
  assert(a.type == ANY_TYPE_SHORT);
  return a.value._short;
}
unsigned short any_to_ushort(Any a)
{
  assert(a.type == ANY_TYPE_USHORT);
  return a.value._unsigned_short;
}

int any_to_int(Any a)
{
  assert(a.type == ANY_TYPE_INT);
  return a.value._int;
}
unsigned int any_to_uint(Any a)
{
  assert(a.type == ANY_TYPE_UINT);
  return a.value._unsigned_int;
}

long any_to_long(Any a)
{
  assert(a.type == ANY_TYPE_LONG);
  return a.value._long;
}
unsigned long any_to_ulong(Any a)
{
  assert(a.type == ANY_TYPE_ULONG);
  return a.value._unsigned_long;
}

long long any_to_long_long(Any a)
{
  assert(a.type == ANY_TYPE_LONGLONG);
  return a.value._long_long;
}
unsigned long long any_to_ulong_long(Any a)
{
  assert(a.type == ANY_TYPE_ULONGLONG);
  return a.value._unsigned_long_long;
}

float any_to_float(Any a)
{
  assert(a.type == ANY_TYPE_FLOAT);
  return a.value._float;
}
double any_to_double(Any a)
{
  assert(a.type == ANY_TYPE_DOUBLE);
  return a.value._double;
}

bool any_to_bool(Any a)
{
  assert(a.type == ANY_TYPE_BOOL);
  return a.value._bool;
}

void * any_to_void(Any a)
{
  assert(a.type == ANY_TYPE_POINTER);
  return a.value._void;
}
void * any_to_ptr(Any a)
{
  return any_to_void(a);
}
void * any_to_pointer(Any a)
{
  return any_to_void(a);
}

char * any_to_string(Any a)
{
  assert(a.type == ANY_TYPE_STRING);
  return a.value._string;
}
char * any_to_str(Any a)
{
  return any_to_string(a);
}




bool any_equals(Any a, Any b)
{
  if (a.type != b.type)
    return false;

  switch (a.type)
  {
    case ANY_TYPE_CHAR:
      return a.value._char == b.value._char;
    case ANY_TYPE_SCHAR:
      return a.value._signed_char == b.value._signed_char;
    case ANY_TYPE_UCHAR:
      return a.value._unsigned_char == b.value._unsigned_char;

    case ANY_TYPE_SHORT:
      return a.value._short == b.value._short;
    case ANY_TYPE_USHORT:
      return a.value._unsigned_short == b.value._unsigned_short;

    case ANY_TYPE_INT:
      return a.value._int == b.value._int;
    case ANY_TYPE_UINT:
      return a.value._unsigned_int == b.value._unsigned_int;

    case ANY_TYPE_LONG:
      return a.value._long == b.value._long;
    case ANY_TYPE_ULONG:
      return a.value._unsigned_long == b.value._unsigned_long;

    case ANY_TYPE_LONGLONG:
      return a.value._long_long == b.value._long_long;
    case ANY_TYPE_ULONGLONG:
      return a.value._unsigned_long_long == b.value._unsigned_long_long;

    case ANY_TYPE_FLOAT:
      return a.value._float == b.value._float;
    case ANY_TYPE_DOUBLE:
      return a.value._double == b.value._double;

    case ANY_TYPE_BOOL:
      return a.value._bool == b.value._bool;

    case ANY_TYPE_POINTER:
      return a.value._void == b.value._void;
    case ANY_TYPE_STRING:
      return a.value._string == b.value._string;

    default:
      assert(0);

  }

}
