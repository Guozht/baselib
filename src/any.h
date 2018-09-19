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


#ifndef __BASELIB_ANY_H
#define __BASELIB_ANY_H

#include <stdbool.h>
#include <sys/types.h>

enum AnyType
{
  ANY_TYPE_CHAR      = 0x0,
  ANY_TYPE_SCHAR     = 0x1,
  ANY_TYPE_UCHAR     = 0x2,

  ANY_TYPE_SHORT     = 0x3,
  ANY_TYPE_USHORT    = 0x4,

  ANY_TYPE_INT       = 0x5,
  ANY_TYPE_UINT      = 0x6,

  ANY_TYPE_LONG      = 0x7,
  ANY_TYPE_ULONG     = 0x8,

  ANY_TYPE_LONGLONG  = 0x9,
  ANY_TYPE_ULONGLONG = 0xA,

  ANY_TYPE_FLOAT     = 0xB,
  ANY_TYPE_DOUBLE    = 0xC,

  ANY_TYPE_BOOL      = 0xD,

  ANY_TYPE_POINTER   = 0xE,
  ANY_TYPE_STRING    = 0xF,

};

union _Any
{
  char _char;
  signed char _signed_char;
  unsigned char _unsigned_char;

  short _short;
  unsigned short _unsigned_short;

  int _int;
  unsigned int _unsigned_int;

  long _long;
  unsigned long _unsigned_long;

  long long _long_long;
  unsigned long long _unsigned_long_long;

  float _float;
  double _double;
  /* long double _long_double; */

  bool _bool;
  void * _void;
  char * _string;

};

struct Any
{
  enum AnyType type;
  union _Any value;
};
typedef struct Any Any;


size_t any_sizeof(enum AnyType type);

Any char_to_any(char c);
Any schar_to_any(signed char c);
Any uchar_to_any(unsigned char c);

Any short_to_any(short s);
Any ushort_to_any(unsigned short s);

Any int_to_any(int i);
Any uint_to_any(unsigned int i);

Any long_to_any(long l);
Any ulong_to_any(unsigned int l);

Any long_long_to_any(long long l);
Any ulong_long_to_any(unsigned long long l);

Any float_to_any(float f);
Any double_to_any(double d);

Any bool_to_any(bool b);

Any void_to_any(void * v);
Any ptr_to_any(void * v);
Any pointer_to_any(void * v);

Any string_to_any(char * str);
Any str_to_any(char * str);



char any_to_char(Any a);
signed char any_to_schar(Any a);
unsigned char any_to_uchar(Any a);

short any_to_short(Any a);
unsigned short any_to_ushort(Any a);

int any_to_int(Any a);
unsigned int any_to_uint(Any a);

long any_to_long(Any a);
unsigned long any_to_ulong(Any a);

long long any_to_long_long(Any a);
unsigned long long any_to_ulong_long(Any a);

float any_to_float(Any a);
double any_to_double(Any a);

bool any_to_bool(Any a);

void * any_to_void(Any a);
void * any_to_ptr(Any a);
void * any_to_pointer(Any a);

char * any_to_string(Any a);
char * any_to_str(Any a);




bool any_equals(Any a, Any b);
char * any_get_string_representation(Any a);



#endif
