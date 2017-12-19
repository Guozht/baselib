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

enum AnyType
{
  ANY_TYPE_CHAR,
  ANY_TYPE_SCHAR,
  ANY_TYPE_UCHAR,

  ANY_TYPE_SHORT,
  ANY_TYPE_USHORT,

  ANY_TYPE_INT,
  ANY_TYPE_UINT,

  ANY_TYPE_LONG,
  ANY_TYPE_ULONG,

  ANY_TYPE_LONGLONG,
  ANY_TYPE_ULONGLONG,

  ANY_TYPE_FLOAT,
  ANY_TYPE_DOUBLE,

  ANY_TYPE_BOOL,

  ANY_TYPE_POINTER,
  ANY_TYPE_STRING,

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
