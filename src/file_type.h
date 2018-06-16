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


#ifndef __FILE_TYPE_H
#define __FILE_TYPE_H


enum FileType
{
  FILE_TYPE_NONE       = 0x00,
  FILE_TYPE_DIRECTORY  = 0x01,
  FILE_TYPE_LINK       = 0x02,
  FILE_TYPE_REGULAR    = 0x04,
  FILE_TYPE_BLOCK      = 0x08,
  FILE_TYPE_CHAR       = 0x10,
  FILE_TYPE_FIFO       = 0x20,
  FILE_TYPE_SOCKET     = 0x40,
  FILE_TYPE_UNKNOWN    = 0x80,
};
typedef enum FileType FileType;


#endif


