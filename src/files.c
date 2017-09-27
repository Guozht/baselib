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


#include "files.h"
#include "utilities.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>  

#define BUFFER_SIZE 0x3FF


char * files_resolve(char * base, char * path)
{
  assert(0); /* NOT YET IMPLEMENTED */
}


bool files_exists(char * path)
{
  assert(path);

  return access(path, F_OK) != -1;
}

long files_size(char * path)
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

char * files_read_all(char * path, size_t * read_ptr)
{
  assert(path);
  assert(read);

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

  data = (char *) malloc(sizeof(char) * file_size);
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
      free(data);
      return NULL;
    }

    read_size += read;
  }
  while (read_size < file_size);
  

  *read_ptr = file_size;
  return data;  
}

bool files_write_all(char * path, char * data, size_t data_length, int op_type)
{
  assert(path);
  assert(data || data_length == 0);
  assert(op_type);

  FILE * file;
  size_t write_size, write;

  if (files_exists(path))
  {
    if (op_type & FILES_OVERWRITE)
      file = fopen(path, "w");
    else if (op_type & FILES_APPEND)
      file = fopen(path, "a");
    else
      file = NULL;
  }
  else
  {
    if (op_type & FILES_CREATE)
      file = fopen(path, "w");
    else
      file = NULL;
  }

  if (!file)
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

