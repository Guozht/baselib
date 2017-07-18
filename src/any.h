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


#ifndef __ANY_H
#define __ANY_H

#include <stdbool.h>


typedef union Any
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
  void * ptr;
  char * string;


}
Any;


#endif
