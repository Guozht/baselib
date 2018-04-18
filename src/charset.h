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


#ifndef __BASELIB_CHARSET_H
#define __BASELIB_CHARSET_H

#include <stdbool.h>

enum Charset
{
  CHARSET_NONE            =  0x0,

  /* modifiers */
  CHARSET_BIG_ENDIAN      =  0x8000,
  CHARSET_LITTLE_ENDIAN   =  0x4000,

  CHARSET_ENDIANNESS_MASK = ~0xC000,

  /* charset of the gods */
  CHARSET_ASCII           = 0xFFF,


  /* unicode */

  CHARSET_UTF1            = 0x1,
  CHARSET_UTF7            = 0x7,
  CHARSET_UTF8            = 0x8,
  CHARSET_UTF16           = 0x16,
  CHARSET_UTF16BE         = CHARSET_UTF16 | CHARSET_BIG_ENDIAN,
  CHARSET_UTF16LE         = CHARSET_UTF16 | CHARSET_LITTLE_ENDIAN,
  CHARSET_UTF32           = 0x32,
  CHARSET_UTF32BE         = CHARSET_UTF32 | CHARSET_BIG_ENDIAN,
  CHARSET_UTF32LE         = CHARSET_UTF32 | CHARSET_LITTLE_ENDIAN,

  /* ISO/IEC 8859 */

  CHARSET_ISO_8859_1  = 0x100,
  CHARSET_ISO_8859_2  = 0x101,
  CHARSET_ISO_8859_3  = 0x102,
  CHARSET_ISO_8859_4  = 0x103,
  CHARSET_ISO_8859_5  = 0x104,
  CHARSET_ISO_8859_6  = 0x105,
  CHARSET_ISO_8859_7  = 0x106,
  CHARSET_ISO_8859_8  = 0x107,
  CHARSET_ISO_8859_9  = 0x108,
  CHARSET_ISO_8859_10 = 0x109,
  CHARSET_ISO_8859_11 = 0x10A,
  CHARSET_ISO_8859_12 = 0x10B,
  CHARSET_ISO_8859_13 = 0x10C,
  CHARSET_ISO_8859_14 = 0x10D,
  CHARSET_ISO_8859_15 = 0x10E,
  CHARSET_ISO_8859_16 = 0x10F,

  /* yes, I'm aware these were meant as april fool's day jokes */
  CHARSET_UTF9            = 0x9,
  CHARSET_UTF18           = 0x18,

  CHARSET_UTF18BE         = CHARSET_UTF18 | CHARSET_BIG_ENDIAN,
  CHARSET_UTF18LE         = CHARSET_UTF18 | CHARSET_LITTLE_ENDIAN,


};
typedef enum Charset Charset;


bool charset_specifies_endianness(Charset charset);
bool charset_is_big_endian(Charset charset);
bool charset_is_little_endian(Charset charset);
Charset charset_get_without_endianness(Charset charset);

Charset charset_parse_name(char * string);
char * charset_to_string(Charset charset);

#endif
