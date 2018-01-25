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


#include <assert.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "file_op.h"
#include "mtest.h"
#include "strings.h"
#include "string_builder.h"
#include "unicode.h"
#include "utilities.h"


#include "files.h"

#define BUFFER_SIZE 0x3FF


#define DEFAULT_LINE_FEED_SEQUENCE "\n"



static bool files_open_write_stream(char * path, FileOp op_type, FILE ** file)
{
  if (files_exists(path))
  {
    if (op_type & FILE_OP_OVERWRITE)
      *file = fopen(path, "wb");
    else if (op_type & FILE_OP_APPEND)
      *file = fopen(path, "ab");
    else
      *file = NULL;
  }
  else
  {
    if (op_type & FILE_OP_CREATE)
      *file = fopen(path, "wb");
    else
      *file = NULL;
  }

  if (*file)
    return true;
  else
    return false;
}

static List * files_path_to_list(char * path, bool * rooted_ptr)
{
  if (strings_equals(path, "/"))
  {
    if (rooted_ptr)
      *rooted_ptr = true;
    return list_new(LIST_TYPE_ARRAY_LIST);
  }

  bool
    starts_with_slash = strings_starts_with(path, "/"),
    ends_with_slash = strings_ends_with(path, "/");

  path = strings_substring(
      path,
      starts_with_slash ? 1 : 0,
      strings_length(path) - (ends_with_slash ? 1 : 0)
    );
  if (rooted_ptr)
    *rooted_ptr = starts_with_slash;

  List * list = strings_split(path, '/');
  _free(path);


  if (list_contains(list, str_to_any("")))
  {
    list_destroy_and_free(list);
    return NULL;
  }

  return list;
}

static void files_normalize_path_list(List * list)
{
  list_remove_and_free(list, str_to_any("."));
  char * current, * last;

  for (unsigned int k = 0; k < list_size(list); k++)
  {
    current = any_to_str(list_get(list, k));
    if (k != 0 && strings_equals(current, ".."))
    {
      last = any_to_string(list_get(list, k - 1));
      if (!strings_equals(last, ".."))
      {
        list_remove_at(list, k);
        list_remove_at(list, k - 1);
        _free(current);
        _free(last);
        k -= 2;
      }
    }
  }
}

static char * files_path_list_to_string(List * list, bool base_rooted)
{
  StringBuilder * sb = string_builder_new();

  if (base_rooted)
    string_builder_append_char(sb, '/');

  if (list_size(list) == 0)
  {
    if (!base_rooted)
      string_builder_append_char(sb, '.');
    return string_builder_to_string_destroy(sb);
  }

  string_builder_append(sb, any_to_str(list_get(list, 0)));
  for (unsigned int k = 1; k < list_size(list); k++)
  {
    string_builder_append_char(sb, '/');
    string_builder_append(sb, any_to_str(list_get(list, k)));
  }

  return string_builder_to_string_destroy(sb);
}


char * files_resolve(char * base, char * path)
{
  assert(!strings_is_null_or_empty(base));
  assert(!strings_is_null_or_empty(path));

  List * base_list, * path_list;
  bool base_rooted;
  char * ret;

  base_list = files_path_to_list(base, &base_rooted);
  if (!base_list)
    return NULL;

  path_list = files_path_to_list(path, NULL);
  if (!path_list)
  {
    list_destroy_and_free(base_list);
    return NULL;
  }

  list_add_range(base_list, path_list);
  files_normalize_path_list(base_list);

  ret = files_path_list_to_string(base_list, base_rooted);

  list_destroy_and_free(base_list);
  list_destroy(path_list);

  return ret;
}


bool files_exists(char * path)
{
  assert(path);

  return access(path, F_OK) != -1;
}

ssize_t files_size(char * path)
{
  assert(path);

  FILE * file = fopen(path, "r");
  if (!file)
    return -1;

  if (fseek(file, 0L, SEEK_END))
  {
    fclose(file);
    return -1;
  }

  long ret = ftell(file);
  fclose(file);

  return ret;
}

char * files_read_all(char * path, ssize_t * read_ptr)
{
  assert(path);
  assert(read_ptr);

  size_t file_size, read_size, read;
  FILE * file;
  char * data;

  file = fopen(path, "r");
  if (!file)
  {
    /* file does not exist */
    *read_ptr = -1;
    return NULL;
  }

  file_size = files_size(path);
  if (file_size == -1)
  {
    /* failed to determine file size */
    *read_ptr = -1;
    return NULL;
  }
  if (file_size == 0)
  {
    /* file is empty, but exists */
    *read_ptr = 0;
    return NULL;
  }

  data = (char *) _malloc(sizeof(char) * file_size);
  read_size = 0;
  do
  {
    read = fread(
        &data[read_size],
        sizeof(char),
        utilities_lmin(BUFFER_SIZE, file_size - read_size),
        file
      );

    if (read <= 0)
    {
      /* read failed before end of file */
      *read_ptr = -1;
      _free(data);
      return NULL;
    }

    read_size += read;
  }
  while (read_size < file_size);


  *read_ptr = file_size;
  return data;
}

List * files_read_all_lines(
    char * path,
    UnicodeEncodingType type
  )
{
  return files_read_all_lines_with_lf(path, type, NULL);
}

List * files_read_all_lines_with_lf(
    char * path,
    UnicodeEncodingType type,
    char * line_feed_sequence
  )
{
  List * ret;
  unsigned int ret_length;
  uint32_t * code_points;
  char * data;
  size_t data_length, code_points_length;
  ssize_t read_length;

  assert(path);

  if (!line_feed_sequence)
    line_feed_sequence = DEFAULT_LINE_FEED_SEQUENCE;

  data = files_read_all(path, &read_length);
  if (read_length == -1)
    return NULL;
  else if (read_length == 0)
    return list_new(LIST_TYPE_LINKED_LIST);

  if (!unicode_is_well_formed(type, data, (size_t) read_length))
  {
    _free(data);
    return NULL;
  }

  code_points = unicode_read_string(type, data, (size_t) read_length, &code_points_length);
  _free(data);
  data = unicode_write_string_utf8(code_points, code_points_length, &data_length);
  _free(code_points);

  if (data_length != strings_length(data)) /* must contain null terminator */
  {
    _free(data);
    return NULL;
  }

  ret = strings_split_by_string(data, line_feed_sequence);
  ret_length = list_size(ret);

  if (
      ret_length > 1 &&
      strings_equals(any_to_str(list_get(ret, ret_length - 1)), "")
    )
  {
    Any removed = list_remove_at(ret, ret_length - 1);

    _free(any_to_str(
      removed
      ));
  }

  _free(data);
  return ret;
}

bool files_write_all(char * path, char * data, size_t data_length, FileOp op_type)
{
  assert(path);
  assert(data || data_length == 0);
  assert(op_type);

  FILE * file;
  size_t write_size, write;

  if (!files_open_write_stream(path, op_type, &file))
    return false;

  write_size = 0;
  while (write_size < data_length)
  {
    write = fwrite(
        data,
        sizeof(char),
        utilities_lmin(data_length - write_size, BUFFER_SIZE),
        file
      );

    if (write <= 0)
    {
      fclose(file);
      return false;
    }

    write_size += write;
  }

  fclose(file);
  return true;
}

bool files_write_all_lines(
    char * path,
    List * lines,
    UnicodeEncodingType type,
    FileOp op_type
  )
{
  return files_write_all_lines_with_lf(
      path,
      lines,
      type,
      op_type,
      NULL
    );
}


bool files_write_all_lines_with_lf(
    char * path,
    List * lines,
    UnicodeEncodingType type,
    FileOp op_type,
    char * line_feed_sequence
  )
{
  assert(path);
  assert(lines);
  assert(list_size(lines) > 0);
  assert(op_type);

  if (!line_feed_sequence)
    line_feed_sequence = DEFAULT_LINE_FEED_SEQUENCE;
  else
    assert(!strings_is_empty(line_feed_sequence));

  bool ret;
  ListTraversal * trav;
  StringBuilder * sb;
  char * line, * data;
  uint32_t * code_points;
  size_t code_points_length, data_length;

  sb = string_builder_new();
  trav = list_get_traversal(lines);
  while (!list_traversal_completed(trav))
  {
    line = any_to_str(list_traversal_next(trav));
    string_builder_append(sb, line);
    string_builder_append(sb, line_feed_sequence);
  }

  data = string_builder_to_string_destroy(sb);
  data_length = strings_length(data);
  code_points = unicode_read_string_utf8(
      data,
      data_length,
      &code_points_length
    );

  _free(data);
  data = unicode_write_string(
      type,
      code_points,
      code_points_length,
      &data_length
    );
  _free(code_points);

  ret = files_write_all(path, data, data_length, op_type);
  _free(data);

  return ret;
}


bool files_delete(char * path)
{
  assert(path);

  return remove(path) == 0;
}


bool files_mkdir(char * path)
{
  assert(path);

  return mkdir(path, 0) == 0;
}

bool files_rmdir(char * path)
{
  assert(path);

  return rmdir(path) == 0;
}
