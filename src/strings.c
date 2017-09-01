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

#include "strings.h"
#include "any.h"
#include "string_builder.h"
#include "chars.h"
#include "list.h"
#include "linked_list.h"

#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>


#define STRINGS_TRIM_FRONT_SIDE 1
#define STRINGS_TRIM_BACK_SIDE  2
#define STRINGS_TRIM_BOTH_SIDES 3



/* internal methods */

static char * strings_alloc(unsigned int size)
{
  char * ret = malloc(size * sizeof(char));
  assert(ret);

  return ret;
}

static bool strings_bounded_equals(char * a, char * b, unsigned int size)
{
  if (size == 0)
    return true;

  return memcmp(a, b, sizeof(char) * size) == 0;
}

static bool strings_bounded_equals_ignore_case(char * a, char * b, unsigned int size)
{
  for (unsigned int k = 0; k < size; k++)
  {
    if (!chars_equals_ignore_case(a[k], b[k]))
      return false;
  }

  return true;
}

static char * strings_to_something(char * string, char (*mapping_function)(char))
{
  assert(string);

  unsigned int string_length = strings_length(string);
  char * ret = strings_alloc(string_length + 1);

  for (unsigned int k = 0; k < string_length; k++)
  {
    ret[k] = mapping_function(string[k]);
  }
  ret[string_length] = '\0';

  return ret;
}

static char * strings_replace_imp(char * string, char old_char, char new_char, bool (*equals_function)(char, char))
{
  assert(string);

  unsigned int string_length = strings_length(string);
  char * ret = strings_alloc(string_length + 1);

  for (unsigned int k = 0; k < string_length; k++)
  {
    if (equals_function(string[k], old_char))
      ret[k] = new_char;
    else
      ret[k] = string[k];
  }
  ret[string_length] = '\0';

  return ret;
}

static char * strings_replace_string_imp(char * string, char * old_string, char * new_string, bool (*equals_function)(char *, char *, unsigned int))
{
  assert(string);
  assert(old_string);
  assert(new_string);

  unsigned int
    string_length = strings_length(string),
    old_string_length = strings_length(old_string)
    ;

  assert(old_string_length > 0);

  StringBuilder * sb = string_builder_new();

  unsigned int k;
  for (k = 0; k < string_length - old_string_length + 1; k++)
  {
    if (equals_function(&string[k], old_string, old_string_length))
    {
      string_builder_append(sb, new_string);
      k += old_string_length - 1;
    }
    else
      string_builder_append_char(sb, string[k]);
  }

  if (old_string_length > 1)
  {
    string_builder_append(sb, &string[k]);
  }

  return string_builder_to_string_destroy(sb);
}

static List * strings_split_up_to_imp(char * string, char split, unsigned int count, bool (*equals_function)(char, char))
{
  assert(string);
  assert(split); /* cannot split by null terminator */

  LinkedList * ret = linked_list_new();
  if (count == 1)
  {
    linked_list_add(ret, string_to_any(strings_clone(string)));
    return (List *) ret;
  }

  StringBuilder * sb = string_builder_new();
  unsigned int
    current_count = 0,
    string_length = strings_length(string);

  for (unsigned int k = 0; k < string_length; k++)
  {
    if (equals_function(string[k], split))
    {
      linked_list_add(ret, string_to_any(string_builder_to_string(sb)));
      string_builder_clear(sb);

      current_count++;
      if (current_count + 1 == count)
      {
        string_builder_append(sb, &string[k + 1]);
        k = string_length; /* terminates loop */
      }
    }
    else
      string_builder_append_char(sb, string[k]);
  }

  linked_list_add(ret, string_to_any(string_builder_to_string(sb)));

  string_builder_destroy(sb);

  return (List *) ret;
}


static List * strings_split_by_string_up_to_imp(char * string, char * split, unsigned int count, bool (*equals_function)(char *, char *, unsigned int))
{
  assert(string);
  assert(split);

  LinkedList * ret = linked_list_new();
  if (count == 1)
  {
    linked_list_add(ret, string_to_any(strings_clone(string)));
    return (List *) ret;
  }
  
  unsigned int
    current_count = 0,
    string_length = strings_length(string),
    split_length = strings_length(split);

  if (split_length == 0)
  {
    for (unsigned int k = 0; k < string_length; k++)
    {
      linked_list_add(ret, string_to_any(strings_from_char(string[k])));
    }

    return (List *) ret;
  }
  

  StringBuilder * sb = string_builder_new();
  
  for (unsigned int k = 0; k < string_length - split_length + 1; k++)
  {
    if (equals_function(&string[k], split, split_length))
    {
      linked_list_add(ret, string_to_any(string_builder_to_string(sb)));
      string_builder_clear(sb);

      k += split_length - 1;

      current_count++;
      if (current_count + 1 == count)
      {
        string_builder_append(sb, &string[k + 1]);
        k = string_length; /* terminates loop */
      }
    }
    else
      string_builder_append_char(sb, string[k]);
  }

  if (current_count + 1 != count)
      string_builder_append(sb, &string[string_length - split_length + 1]);
  
  linked_list_add(ret, string_to_any(string_builder_to_string(sb)));


  string_builder_destroy(sb);

  return (List *) ret;
}

static bool strings_starts_with_imp(char * string, char * start, bool (*equals_function)(char *, char *, unsigned int))
{
  assert(string);
  assert(start);

  unsigned int
    string_length = strings_length(string),
    start_length = strings_length(start);

  if (start_length > string_length)
    return false;

  return equals_function(
      string,
      start,
      start_length
    );
}

static bool strings_ends_with_imp(char * string, char * end, bool (*equals_function)(char *, char *, unsigned int))
{
  assert(string);
  assert(end);

  unsigned int
    string_length = strings_length(string),
    end_length = strings_length(end);

  if (end_length > string_length)
    return false;

  return equals_function(
      &string[string_length - end_length],
      end,
      end_length
    );
}

static bool strings_contains_imp(char * string, char c, bool (*equals_function)(char, char))
{
  assert(string);
  assert(c); /* char may not be 'null' */

  unsigned int
    length = strings_length(string);

  for (unsigned int k = 0; k < length; k++)
  {
    if (equals_function(string[k], c))
      return true;
  }

  return false;
}

static bool strings_contains_string_imp(char * string, char * substring, bool (*equals_function)(char *, char *, unsigned int))
{
  assert(string);
  assert(substring);

  unsigned int
    string_length = strings_length(string),
    substring_length = strings_length(substring);

  for (unsigned int k = 0; k < string_length - substring_length + 1; k++)
  {
    if (equals_function(&string[k], substring, substring_length))
    {
      return true;
    }
  }

  return false;
}

static char * strings_trim_imp(char * string, int control)
{
  assert(string);

  unsigned int
    length = strings_length(string);
  long
    start = 0,
    end = length;

  if (length == 0)
    return strings_empty();

  if (control & STRINGS_TRIM_FRONT_SIDE)
  {
    while (chars_is_white_space(string[start]) && start < length)
      start++;
  }

  if (control & STRINGS_TRIM_BACK_SIDE)
  {
    while (chars_is_white_space(string[end - 1]) && end > start)
      end--;
  }

  return strings_substring(string, (unsigned int) start, (unsigned int) end);
}


/* end of internal methods */


char * strings_empty()
{
  char * ret = strings_alloc(1);
  ret[0] = '\0';

  return ret;
}
char * strings_from_char(char c)
{
  assert(c); /* null character is not valid */

  char * ret = strings_alloc(2);
  ret[0] = c;
  ret[1] = '\0';

  return ret;
}
char * strings_clone(char * string)
{
  assert(string);

  char * ret;
  unsigned int length = strings_length(string);

  ret = strings_alloc(length + 1);

  memcpy(
      ret,
      string,
      (length + 1) * sizeof(char) /* copies null terminator */
    );

  return ret;
}

char strings_char_at(char * string, unsigned int index)
{
  assert(string);

  unsigned int length = strings_length(string);
  assert(index < length);

  return string[index];
}
unsigned int strings_length(char * string)
{
  return strlen(string);
}

char * strings_prefix(char * string, unsigned int length)
{
  assert(string);

  unsigned int string_length = strings_length(string);
  assert(length <= string_length);

  char * ret = strings_alloc(length + 1);

  memcpy(
      ret,
      string,
      length * sizeof(char)
    );
  ret[length] = '\0';

  return ret;
}
char * strings_postfix(char * string, unsigned int length)
{
  assert(string);

  unsigned int string_length = strings_length(string);
  assert(length <= string_length);

  char * ret = strings_alloc(length + 1);

  memcpy(
    ret,
    &string[string_length - length],
    (length + 1) * sizeof(char) /* copies null terminator */
    );

  return ret;
}
char * strings_substring(char * string, unsigned int start, unsigned int end)
{
  assert(string);

  unsigned int string_length = strings_length(string);
  assert(end <= string_length);
  assert(start <= end);

  if (start == end)
    return strings_empty();

  char * ret = strings_alloc(end - start + 1);
  memcpy(
      ret,
      &string[start],
      (end - start) * sizeof(char)
    );

  ret[end - start + 1] = '\0';

  return ret;
}

char * strings_to_lower(char * string)
{
  return strings_to_something(string, chars_to_lower);
}
char * strings_to_upper(char * string)
{
  return strings_to_something(string, chars_to_upper);
}

char * strings_replace(char * string, char old_char, char new_char)
{
  return strings_replace_imp(string, old_char, new_char, chars_equals);
}
char * strings_replace_ignore_case(char * string, char old_char, char new_char)
{
  return strings_replace_imp(string, old_char, new_char, chars_equals_ignore_case);
}
char * strings_replace_string(char * string, char * old_string, char * new_string)
{
  return strings_replace_string_imp(string, old_string, new_string, strings_bounded_equals);
}
char * strings_replace_string_ignore_case(char * string, char * old_string, char * new_string)
{
  return strings_replace_string_imp(string, old_string, new_string, strings_bounded_equals_ignore_case);
}



char * strings_trim(char * string)
{
  return strings_trim_imp(string, STRINGS_TRIM_BOTH_SIDES);
}
char * strings_trim_front(char * string)
{
  return strings_trim_imp(string, STRINGS_TRIM_FRONT_SIDE);
}
char * strings_trim_back(char * string)
{
  return strings_trim_imp(string, STRINGS_TRIM_BACK_SIDE);
}


List * strings_split(char * string, char split)
{
  return strings_split_up_to(string, split, 0);
}
List * strings_split_ignore_case(char * string, char split)
{
  return strings_split_ignore_case_up_to(string, split, 0);
}
List * strings_split_up_to(char * string, char split, unsigned int count)
{
  return strings_split_up_to_imp(string, split, count, chars_equals);
}
List * strings_split_ignore_case_up_to(char * string, char split, unsigned int count)
{
  return strings_split_up_to_imp(string, split, count, chars_equals_ignore_case);
}

List * strings_split_by_string(char * string, char * split)
{
  return strings_split_by_string_up_to(string, split, 0);
}
List * strings_split_by_string_ignore_case(char * string, char * split)
{
  return strings_split_by_string_ignore_case_up_to(string, split, 0);
}
List * strings_split_by_string_up_to(char * string, char * split, unsigned int count)
{
  return strings_split_by_string_up_to_imp(string, split, count, strings_bounded_equals);
}
List * strings_split_by_string_ignore_case_up_to(char * string, char * split, unsigned int count)
{
  return strings_split_by_string_up_to_imp(string, split, count, strings_bounded_equals_ignore_case);
}



bool strings_starts_with(char * string, char * start)
{
  return strings_starts_with_imp(string, start, strings_bounded_equals);
}
bool strings_starts_with_ignore_case(char * string, char * start)
{
  return strings_starts_with_imp(string, start, strings_bounded_equals_ignore_case);
}
bool strings_ends_with(char * string, char * end)
{
  return strings_ends_with_imp(string, end, strings_bounded_equals);
}
bool strings_ends_with_ignore_case(char * string, char * end)
{
  return strings_ends_with_imp(string, end, strings_bounded_equals_ignore_case);
}



bool strings_contains(char * string, char c)
{
  return strings_contains_imp(string, c, chars_equals);
}

bool strings_contains_ignore_case(char * string, char c)
{
  return strings_contains_imp(string, c, chars_equals_ignore_case);
}
bool strings_contains_string(char * string, char * substring)
{
  return strings_contains_string_imp(string, substring, strings_bounded_equals);
}
bool strings_contains_string_ignore_case(char * string, char * substring)
{
  return strings_contains_string_imp(string, substring, strings_bounded_equals_ignore_case);
}


bool strings_equals(char * string1, char * string2)
{
  assert(string1);
  assert(string2);

  return !strcmp(string1, string2);
}
bool strings_equals_ignore_case(char * string1, char * string2)
{
  assert(string1);
  assert(string2);

  unsigned int
    length1 = strings_length(string1),
    length2 = strings_length(string2);

  if (length1 != length2)
    return false;

  for (unsigned int k = 0; k < length1; k++)
  {
    if (!chars_equals_ignore_case(string1[k], string2[k]))
      return false;
  }

  return true;
}

bool strings_is_empty(char * string)
{
  assert(string);

  return string[0] == '\0';
}
bool strings_is_white_space(char * string)
{
  assert(string);

  unsigned int length = strings_length(string);

  for (unsigned int k = 0; k < length; k++)
  {
    if (string[k] > 0x20)
      return false;
  }

  return true;
}
bool strings_is_null_or_empty(char * string)
{
  return string == NULL || strings_is_empty(string);
}
bool strings_is_null_or_white_space(char * string)
{
  return string == NULL || strings_is_white_space(string);
}
