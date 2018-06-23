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

#ifndef __FILE_OPERATION_H
#define __FILE_OPERATION_H


enum FileOp
{
  FILE_OP_CREATE = 0x1,
  FILE_OP_APPEND = 0x2,
  FILE_OP_OVERWRITE = 0x4,
  FILE_OP_CLOEXEC = 0x8,
  FILE_OP_MMAP = 0x10,
  FILE_OP_EXCLUSIVE = 0x20,
  FILE_OP_NO_CANCEL_POINTS = 0x40
};
typedef enum FileOp FileOp;


#endif
