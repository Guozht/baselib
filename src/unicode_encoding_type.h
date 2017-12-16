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


#ifndef __BASELIB_UNICODE_ENCODING_TYPE_H
#define __BASELIB_UNICODE_ENCODING_TYPE_H

enum UnicodeEncodingType
{
  UNICODE_ENCODING_TYPE_NONE = 0x0,

  UNICODE_ENCODING_TYPE_UTF1 = 0x1,
  UNICODE_ENCODING_TYPE_UTF7 = 0x7,
  UNICODE_ENCODING_TYPE_UTF8 = 0x8,
  UNICODE_ENCODING_TYPE_UTF16 = 0x16,
  UNICODE_ENCODING_TYPE_UTF16BE = 0x16A,
  UNICODE_ENCODING_TYPE_UTF16LE = 0x16B,
  UNICODE_ENCODING_TYPE_UTF32 = 0x32,
  UNICODE_ENCODING_TYPE_UTF32BE = 0x32A,
  UNICODE_ENCODING_TYPE_UTF32LE = 0x32B,

  /* yes, I'm aware these were meant as april fool's day jokes */
  UNICODE_ENCODING_TYPE_UTF9 = 0x9,
  UNICODE_ENCODING_TYPE_UTF18 = 0x18,
  UNICODE_ENCODING_TYPE_UTF18BE = 0x18A,
  UNICODE_ENCODING_TYPE_UTF18LE = 0x18B,

};
typedef enum UnicodeEncodingType UnicodeEncodingType;


UnicodeEncodingType unicode_parse_encoding_type(char * string);
char * unicode_encoding_type_to_string(UnicodeEncodingType type);

#endif
