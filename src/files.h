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



#ifndef __BASELIB_FILES_H
#define __BASELIB_FILES_H


#include <stdbool.h>
#include <stdint.h>
#include <sys/types.h>

#include "file_op.h"
#include "list.h"
#include "unicode_encoding_type.h"


char * files_resolve(char * base, char * path);


bool files_exists(char * path);
ssize_t files_size(char * path);

char * files_read_all(char * path, ssize_t * read_ptr);
List * files_read_all_lines(
    char * path,
    UnicodeEncodingType type
  );
List * files_read_all_lines_with_lf(
    char * path,
    UnicodeEncodingType type,
    char * line_feed_sequence
  );

bool files_write_all(
    char * path,
    char * data,
    size_t data_length,
    FileOp op_type
  );
bool files_write_all_lines(
    char * path,
    List * lines,
    UnicodeEncodingType type,
    FileOp op_type
  );
bool files_write_all_lines_with_lf(
    char * path,
    List * lines,
    UnicodeEncodingType type,
    FileOp op_type,
    char * line_feed_sequence
  );

bool files_delete(char * path);

bool files_mkdir(char * path);
bool files_rmdir(char * path);

#endif
