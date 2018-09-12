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


#ifndef __BASELIB_PARSING
#define __BASELIB_PARSING

#include <stdbool.h>

bool try_parse_short(char * str, short * value_ptr);
bool try_parse_int(char * str, int * value_ptr);
bool try_parse_long(char * str, long * value_ptr);
bool try_parse_long_long(char * str, long long * value_ptr);

bool try_parse_ushort(char * str, unsigned short * value_ptr);
bool try_parse_uint(char * str, unsigned int * value_ptr);
bool try_parse_ulong(char * str, unsigned long * value_ptr);
bool try_parse_ulong_long(char * str, unsigned long long * value_ptr);

bool try_parse_int8(char * str, int8_t * value_ptr);
bool try_parse_uint8(char * str, uint8_t * value_ptr);
bool try_parse_int16(char * str, int16_t * value_ptr);
bool try_parse_uint16(char * str, uint16_t * value_ptr);
bool try_parse_int32(char * str, int32_t * value_ptr);
bool try_parse_uint32(char * str, uint32_t * value_ptr);
bool try_parse_int64(char * str, int64_t * value_ptr);
bool try_parse_uint64(char * str, uint64_t * value_ptr);


#endif



