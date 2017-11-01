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

#ifndef __BASELIB_STRINGS_H
#define __BASELIB_STRINGS_H

#include <stdbool.h>
#include <stdint.h>

#include "list.h"


char * strings_empty();
char * strings_from_char(char c);
char * strings_clone(char * string);
char * strings_from_array(char * array, unsigned int length);

char strings_char_at(char * string, unsigned int k);
unsigned int strings_length(char * string);

int32_t strings_hash(char * string);

char * strings_prefix(char * string, unsigned int length);
#define strings_suffix(s,l) strings_postfix(s,l)
char * strings_postfix(char * string, unsigned int length);
char * strings_substring(char * string, unsigned int start, unsigned int end);

char * strings_to_lower(char * string);
char * strings_to_upper(char * string);

char * strings_replace(char * string, char oldChar, char newChar);
char * strings_replace_ignore_case(char * string, char oldChar, char newChar);
char * strings_replace_string(char * string, char * oldString, char * newString);
char * strings_replace_string_ignore_case(char * string, char * oldString, char * newString);


char * strings_trim(char * string);
char * strings_trim_front(char * string);
char * strings_trim_back(char * string);

char * strings_concat(char * string1, char * string2);


List * strings_split(char * string, char split);
List * strings_split_ignore_case(char * string, char split);
List * strings_split_up_to(char * string, char split, unsigned int count);
List * strings_split_ignore_case_up_to(char * string, char split, unsigned int count);

List * strings_split_by_string(char * string, char * split);
List * strings_split_by_string_ignore_case(char * string, char * split);
List * strings_split_by_string_up_to(char * string, char * split, unsigned int count);
List * strings_split_by_string_ignore_case_up_to(char * string, char * split, unsigned int count);



bool strings_starts_with(char * string, char * start);
bool strings_starts_with_ignore_case(char * string, char * start);
bool strings_ends_with(char * string, char * end);
bool strings_ends_with_ignore_case(char * string, char * end);


bool strings_contains(char * string, char c);
bool strings_contains_ignore_case(char * string, char c);
bool strings_contains_string(char * string, char * substring);
bool strings_contains_string_ignore_case(char * string, char * substring);

bool strings_equals(char * string1, char * string2);
bool strings_equals_ignore_case(char * string1, char * string2);

bool strings_is_empty(char * string);
#define strings_is_whitespace(s) strings_is_white_space(s)
bool strings_is_white_space(char * string);
bool strings_is_null_or_empty(char * string);
#define strings_is_null_or_whitespace(s) strings_is_null_or_white_space(s)
bool strings_is_null_or_white_space(char * string);



#endif
