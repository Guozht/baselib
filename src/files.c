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
#include <dirent.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "charset.h"
#include "codec.h"
#include "file_op.h"
#include "file_type.h"
#include "mtest.h"
#include "strings.h"
#include "string_builder.h"
#include "unicode.h"
#include "utilities.h"


#include "files.h"

#define BUFFER_SIZE 0xFF
#define DEFAULT_LINE_FEED_SEQUENCE "\n"



static void files_accumulate_data(
    char ** data,
    char * buffer,
    size_t * current,
    size_t buffer_size
  )
{

  if (*data)
  {
    *data = (char *) _realloc(*data, sizeof(char) * (*current + buffer_size));
    assert(*data);

    memcpy(&(*data)[*current], buffer, sizeof(char) * buffer_size);
  }
  else
  {
    *data = (char *) _malloc(sizeof(char) * buffer_size);
    assert(*data);

    memcpy(*data, buffer, sizeof(char) * buffer_size);
  }
  
  *current += buffer_size;
}

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


static FileType files_get_file_type_from_dtype(unsigned char dtype)
{
  switch (dtype)
  {
    case DT_BLK:
      return FILE_TYPE_BLOCK;
    case DT_CHR:
      return FILE_TYPE_CHAR;
    case DT_DIR:
      return FILE_TYPE_DIRECTORY;
    case DT_FIFO:
      return FILE_TYPE_FIFO;
    case DT_LNK:
      return FILE_TYPE_LINK;
    case DT_REG:
      return FILE_TYPE_REGULAR;
    case DT_SOCK:
      return FILE_TYPE_SOCKET;
    case DT_UNKNOWN:
      return FILE_TYPE_UNKNOWN;
    default:
      return FILE_TYPE_NONE;
  }
}

static FileType files_get_file_type_from_stat_mode(mode_t mode)
{
  switch (mode & S_IFMT)
  {
    case S_IFSOCK:
      return FILE_TYPE_SOCKET;
    case S_IFLNK:
      return FILE_TYPE_LINK;
    case S_IFREG:
      return FILE_TYPE_REGULAR;
    case S_IFBLK:
      return FILE_TYPE_BLOCK;
    case S_IFDIR:
      return FILE_TYPE_DIRECTORY;
    case S_IFCHR:
      return FILE_TYPE_CHAR;
    case S_IFIFO:
      return FILE_TYPE_FIFO;
    default:
      return FILE_TYPE_NONE;
  }
}

static List * files_list_imp(char * path, char * extension, FileType type)
{
  List * ret;
  DIR * directory;
  struct dirent * entry;

  directory = opendir(path);
  if (!directory)
    return NULL;

  ret = list_new(LIST_TYPE_LINKED_LIST);

  do
  {
    entry = readdir(directory);
    if (!entry)
      continue;

    if (strings_equals(entry->d_name, ".") ||
        strings_equals(entry->d_name, ".."))
      continue;

    if (extension)
    {
      if (!strings_ends_with(entry->d_name, extension))
        continue;
    }
    if ((files_get_file_type_from_dtype(entry->d_type) & type) == 0)
      continue;

    list_add(ret, str_to_any(strings_clone(entry->d_name)));
  }
  while (entry != NULL);
  closedir(directory);

  return ret;
}


bool files_exists(char * path)
{
  assert(path);

  return access(path, F_OK) != -1;
}

bool files_exists_as(char * path, FileType file_type)
{
  struct stat buffer;
  FileType read_type;

  if (stat(path, &buffer))
    return false;

  read_type = files_get_file_type_from_stat_mode(buffer.st_mode);
  return (read_type & file_type) != 0;
}

FileType files_get_type(char * path)
{
  struct stat buffer;
  
  if (stat(path, &buffer))
    return FILE_TYPE_NONE;
  else
    return files_get_file_type_from_stat_mode(buffer.st_mode);
}

short files_get_permissions(char * path)
{
  struct stat buffer;

  if (stat(path, &buffer))
    return -1;
  else
    return (short) (buffer.st_mode & 0777);
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

  bool continue_read;
  size_t read_size, read;
  FILE * file;
  char * data, buffer [BUFFER_SIZE];

  file = fopen(path, "r");
  if (!file)
  {
    /* file does not exist */
    *read_ptr = -1;
    return NULL;
  }

  read_size = 0;
  data = NULL;
  continue_read = true;
  do
  {
    read = fread(
        buffer,
        sizeof(char),
        BUFFER_SIZE,
        file
      );
   
    if (read > 0)
    {
      files_accumulate_data(
          &data,
          buffer,
          &read_size,
          read
        );
    }

    /* read reached EOF or encountered an error */
    if (read < BUFFER_SIZE)
    {
      continue_read = false;

      if (feof(file)) /* encountered EOF */
      {
        fclose(file);
        *read_ptr = read_size;
      }
      else /* stream errored */
      {
        fclose(file);
        *read_ptr = -1;
        free(data);
        data = NULL;
      }
    }

  }
  while (continue_read);

  return data;
}

List * files_read_all_lines(
    char * path,
    Charset type
  )
{
  return files_read_all_lines_with_lf(path, type, NULL);
}

List * files_read_all_lines_with_lf(
    char * path,
    Charset type,
    char * line_feed_sequence
  )
{
  List * ret;
  Codec * codec;
  unsigned int ret_length;
  uint32_t * code_points;
  char * data;
  size_t data_length, code_points_length;
  ssize_t read_length;

  assert(path);

  codec = codec_new(type);

  if (!line_feed_sequence)
    line_feed_sequence = DEFAULT_LINE_FEED_SEQUENCE;

  data = files_read_all(path, &read_length);
  if (read_length == -1)
    return NULL;
  else if (read_length == 0)
    return list_new(LIST_TYPE_LINKED_LIST);

  if (!codec_is_well_formed(codec, data, (size_t) read_length))
  {
    _free(data);
    codec_destroy(codec);
    return NULL;
  }

  code_points = codec_read_string(codec, data, (size_t) read_length, &code_points_length);
  _free(data);
  data = unicode_write_string_utf8(code_points, code_points_length, &data_length);
  _free(code_points);

  if (data_length != strings_length(data)) /* must contain null terminator */
  {
    _free(data);
    codec_destroy(codec);
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
  codec_destroy(codec);
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
        &data[write_size],
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
    Charset type,
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
    Charset type,
    FileOp op_type,
    char * line_feed_sequence
  )
{
  Codec * codec;
  bool ret;
  ListTraversal * trav;
  StringBuilder * sb;
  char * line, * data;
  uint32_t * code_points;
  size_t code_points_length, data_length;

  assert(path);
  assert(lines);
  assert(list_size(lines) > 0);
  assert(op_type);

  if (!line_feed_sequence)
    line_feed_sequence = DEFAULT_LINE_FEED_SEQUENCE;
  else
    assert(!strings_is_empty(line_feed_sequence));

  codec = codec_new(type);

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

  /* TODO: SHOULD ASSERT REPRESENTABILITY */

  _free(data);
  data = codec_write_string(
      codec,
      code_points,
      code_points_length,
      &data_length
    );
  _free(code_points);
  codec_destroy(codec);

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

  return mkdir(path, 0755) == 0;
}

bool files_rmdir(char * path)
{
  assert(path);

  return rmdir(path) == 0;
}




List * files_list(char * path)
{
  assert(path);

  return files_list_imp(path, NULL, (FileType) -1);
}


List * files_list_with_extension(char * path, char * extension)
{
  assert(path);
  assert(extension);

  unsigned int extension_length = strings_length(extension);
  char extension_mod [extension_length + 2];

  if (!strings_is_empty(extension) && !strings_starts_with(extension, "."))
    sprintf(extension_mod, ".%s", extension);
  else
    memcpy(extension_mod, extension, sizeof(char) * (extension_length + 1));

  return files_list_imp(path, extension, (FileType) -1);
}


List * files_list_of_type(char * path, FileType file_type)
{
  assert(path);

  return files_list_imp(path, NULL, file_type);
}



