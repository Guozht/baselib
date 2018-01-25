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


#ifndef __BASELIB_CHARS_H
#define __BASELIB_CHARS_H


#include <stdbool.h>




bool chars_equals(char c1, char c2);
bool chars_equals_ignore_case(char c1, char c2);

bool chars_is_lower(char c);
bool chars_is_upper(char c);

bool chars_is_alpha(char c);
bool chars_is_digit(char c);
bool chars_is_alpha_or_digit(char c);
bool chars_is_octal_digit(char c);
bool chars_is_hex_digit(char c);
bool chars_is_ascii7(char c);

bool chars_is_white_space(char c);

char chars_to_lower(char c);
char chars_to_upper(char c);


int chars_order(char c1, char c2);
int chars_order_ignore_case(char c1, char c2);




#endif
