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


#ifndef __BASELIB_STRING_BUILDER_H
#define __BASELIB_STRING_BUILDER_H




struct StringBuilder;
typedef struct StringBuilder StringBuilder;


StringBuilder * string_builder_new();
StringBuilder * string_builder_new_with(unsigned int size);

void string_builder_destroy(StringBuilder * sb);

void string_builder_clear(StringBuilder * sb);


unsigned int string_builder_length(StringBuilder * sb);

void string_builder_append(StringBuilder * sb, char * string);
void string_builder_append_char(StringBuilder * sb, char c);
void string_builder_append_int(StringBuilder * sb, long long l);
void string_builder_append_float(StringBuilder * sb, double d);


char * string_builder_to_string(StringBuilder * sb);
char * string_builder_to_temp_string(StringBuilder * sb);
char * string_builder_to_string_destroy(StringBuilder * sb);






#endif
