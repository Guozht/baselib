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

#include "charset.h"
#include "list.h"
#include "strings.h"


/*
bool charset_specifies_endianness(Charset charset)
{
  return charset_is_big_endian(charset) || charset_is_little_endian(charset);
}
bool charset_is_big_endian(Charset charset)
{
  return (charset & CHARSET_BIG_ENDIAN) != 0;
}
bool charset_is_little_endian(Charset charset)
{
  return (charset & CHARSET_LITTLE_ENDIAN) != 0;
}
Charset charset_get_without_endianness(Charset charset)
{
  return charset & CHARSET_ENDIANNESS_MASK;
}
*/


List * charset_list()
{
  List * ret;

  ret = list_new(LIST_TYPE_ARRAY_LIST);

  list_add(ret, int_to_any(CHARSET_ASCII));
  list_add(ret, int_to_any(CHARSET_UTF1));
  list_add(ret, int_to_any(CHARSET_UTF7));
  list_add(ret, int_to_any(CHARSET_UTF8));
  list_add(ret, int_to_any(CHARSET_UTF16));
  list_add(ret, int_to_any(CHARSET_UTF16BE));
  list_add(ret, int_to_any(CHARSET_UTF16LE));
  list_add(ret, int_to_any(CHARSET_UTF32));
  list_add(ret, int_to_any(CHARSET_UTF32BE));
  list_add(ret, int_to_any(CHARSET_UTF32LE));
  list_add(ret, int_to_any(CHARSET_ISO_8859_1));
  list_add(ret, int_to_any(CHARSET_ISO_8859_2));
  list_add(ret, int_to_any(CHARSET_ISO_8859_3));
  list_add(ret, int_to_any(CHARSET_ISO_8859_4));
  list_add(ret, int_to_any(CHARSET_ISO_8859_5));
  list_add(ret, int_to_any(CHARSET_ISO_8859_6));
  list_add(ret, int_to_any(CHARSET_ISO_8859_7));
  list_add(ret, int_to_any(CHARSET_ISO_8859_8));
  list_add(ret, int_to_any(CHARSET_ISO_8859_9));
  list_add(ret, int_to_any(CHARSET_ISO_8859_10));
  list_add(ret, int_to_any(CHARSET_ISO_8859_11));
  list_add(ret, int_to_any(CHARSET_ISO_8859_12));
  list_add(ret, int_to_any(CHARSET_ISO_8859_13));
  list_add(ret, int_to_any(CHARSET_ISO_8859_14));
  list_add(ret, int_to_any(CHARSET_ISO_8859_15));
  list_add(ret, int_to_any(CHARSET_ISO_8859_16));
  list_add(ret, int_to_any(CHARSET_UTF9));
  list_add(ret, int_to_any(CHARSET_UTF18));
  list_add(ret, int_to_any(CHARSET_UTF18BE));
  list_add(ret, int_to_any(CHARSET_UTF18LE));

  return ret;
}



Charset charset_parse_name(char * string)
{
  assert(string);

  if (
    strings_equals_ignore_case(string, "ASCII") ||
    strings_equals_ignore_case(string, "US-ASCII") ||
    strings_equals_ignore_case(string, "ASCII7") ||
    strings_equals_ignore_case(string, "US-ASCII7")
    )
    return CHARSET_ASCII;
  else if (
    strings_equals_ignore_case(string, "UTF-1") ||
    strings_equals_ignore_case(string, "UTF1")
    )
    return CHARSET_UTF1;
  else if (
    strings_equals_ignore_case(string, "UTF-7") ||
    strings_equals_ignore_case(string, "UTF7")
    )
    return CHARSET_UTF7;
  else if (
    strings_equals_ignore_case(string, "UTF-8") ||
    strings_equals_ignore_case(string, "UTF8")
    )
    return CHARSET_UTF8;
  else if (
    strings_equals_ignore_case(string, "UTF-16") ||
    strings_equals_ignore_case(string, "UTF16")
    )
    return CHARSET_UTF16;
  else if (
    strings_equals_ignore_case(string, "UTF-16BE") ||
    strings_equals_ignore_case(string, "UTF16BE")
    )
    return CHARSET_UTF16BE;
  else if (
    strings_equals_ignore_case(string, "UTF-16LE") ||
    strings_equals_ignore_case(string, "UTF16LE")
    )
    return CHARSET_UTF16LE;
  else if (
    strings_equals_ignore_case(string, "UTF-32") ||
    strings_equals_ignore_case(string, "UTF32")
    )
    return CHARSET_UTF32;
  else if (
    strings_equals_ignore_case(string, "UTF-32BE") ||
    strings_equals_ignore_case(string, "UTF32BE")
    )
    return CHARSET_UTF32BE;
  else if (
    strings_equals_ignore_case(string, "UTF-32LE") ||
    strings_equals_ignore_case(string, "UTF32LE")
    )
    return CHARSET_UTF32LE;
  else if (
    strings_equals_ignore_case(string, "UTF-9") ||
    strings_equals_ignore_case(string, "UTF9")
    )
    return CHARSET_UTF9;
  else if (
    strings_equals_ignore_case(string, "UTF-18") ||
    strings_equals_ignore_case(string, "UTF18"))
    return CHARSET_UTF18;
  else if (
    strings_equals_ignore_case(string, "UTF-18BE") ||
    strings_equals_ignore_case(string, "UTF18BE")
    )
    return CHARSET_UTF18BE;
  else if (
    strings_equals_ignore_case(string, "UTF-18LE") ||
    strings_equals_ignore_case(string, "UTF18LE")
    )
    return CHARSET_UTF18LE;
  else if (
    strings_equals_ignore_case(string, "ISO/IEC 8859-1") ||
    strings_equals_ignore_case(string, "ISO-8859-1") ||
    strings_equals_ignore_case(string, "ISO 8859-1") ||
    strings_equals_ignore_case(string, "ISO8859-1") ||
    strings_equals_ignore_case(string, "LATIN 1") ||
    strings_equals_ignore_case(string, "LATIN-1") || 
    strings_equals_ignore_case(string, "LATIN1")
    )
    return CHARSET_ISO_8859_1;
  else if (
    strings_equals_ignore_case(string, "ISO/IEC 8859-2") ||
    strings_equals_ignore_case(string, "ISO-8859-2") ||
    strings_equals_ignore_case(string, "ISO 8859-2") ||
    strings_equals_ignore_case(string, "ISO8859-2") ||
    strings_equals_ignore_case(string, "LATIN 2") ||
    strings_equals_ignore_case(string, "LATIN-2") || 
    strings_equals_ignore_case(string, "LATIN2")
    )
    return CHARSET_ISO_8859_2;
  else if (
    strings_equals_ignore_case(string, "ISO/IEC 8859-3") ||
    strings_equals_ignore_case(string, "ISO-8859-3") ||
    strings_equals_ignore_case(string, "ISO 8859-3") ||
    strings_equals_ignore_case(string, "ISO8859-3") ||
    strings_equals_ignore_case(string, "LATIN 3") ||
    strings_equals_ignore_case(string, "LATIN-3") || 
    strings_equals_ignore_case(string, "LATIN3")
    )
    return CHARSET_ISO_8859_3;
  else if (
    strings_equals_ignore_case(string, "ISO/IEC 8859-4") ||
    strings_equals_ignore_case(string, "ISO-8859-4") ||
    strings_equals_ignore_case(string, "ISO 8859-4") ||
    strings_equals_ignore_case(string, "ISO8859-4") ||
    strings_equals_ignore_case(string, "LATIN 4") ||
    strings_equals_ignore_case(string, "LATIN-4") || 
    strings_equals_ignore_case(string, "LATIN4")
    )
    return CHARSET_ISO_8859_4;
  else if (
    strings_equals_ignore_case(string, "ISO/IEC 8859-5") ||
    strings_equals_ignore_case(string, "ISO-8859-5") ||
    strings_equals_ignore_case(string, "ISO 8859-5") ||
    strings_equals_ignore_case(string, "ISO8859-5") ||
    strings_equals_ignore_case(string, "LATIN/CYRILLIC") ||
    strings_equals_ignore_case(string, "LATIN-CYRILLIC")
    )
    return CHARSET_ISO_8859_5;
  else if (
    strings_equals_ignore_case(string, "ISO/IEC 8859-6") ||
    strings_equals_ignore_case(string, "ISO-8859-6") ||
    strings_equals_ignore_case(string, "ISO 8859-6") ||
    strings_equals_ignore_case(string, "ISO8859-6") ||
    strings_equals_ignore_case(string, "LATIN/ARABIC") ||
    strings_equals_ignore_case(string, "LATIN-ARABIC")
    )
    return CHARSET_ISO_8859_6;
  else if (
    strings_equals_ignore_case(string, "ISO/IEC 8859-7") ||
    strings_equals_ignore_case(string, "ISO-8859-7") ||
    strings_equals_ignore_case(string, "ISO 8859-7") ||
    strings_equals_ignore_case(string, "ISO8859-7") ||
    strings_equals_ignore_case(string, "LATIN/GREEK") ||
    strings_equals_ignore_case(string, "LATIN-GREEK")
    )
    return CHARSET_ISO_8859_7;
  else if (
    strings_equals_ignore_case(string, "ISO/IEC 8859-8") ||
    strings_equals_ignore_case(string, "ISO-8859-8") ||
    strings_equals_ignore_case(string, "ISO 8859-8") ||
    strings_equals_ignore_case(string, "ISO8859-8") ||
    strings_equals_ignore_case(string, "LATIN/HEBREW") ||
    strings_equals_ignore_case(string, "LATIN-HEBREW")
    )
    return CHARSET_ISO_8859_8;
  else if (
    strings_equals_ignore_case(string, "ISO/IEC 8859-9") ||
    strings_equals_ignore_case(string, "ISO-8859-9") ||
    strings_equals_ignore_case(string, "ISO 8859-9") ||
    strings_equals_ignore_case(string, "ISO8859-9") ||
    strings_equals_ignore_case(string, "LATIN 5") ||
    strings_equals_ignore_case(string, "LATIN-5") ||
    strings_equals_ignore_case(string, "LATIN5")
    )
    return CHARSET_ISO_8859_9;
  else if (
    strings_equals_ignore_case(string, "ISO/IEC 8859-10") ||
    strings_equals_ignore_case(string, "ISO-8859-10") ||
    strings_equals_ignore_case(string, "ISO 8859-10") ||
    strings_equals_ignore_case(string, "ISO8859-10") ||
    strings_equals_ignore_case(string, "LATIN 6") ||
    strings_equals_ignore_case(string, "LATIN-6") ||
    strings_equals_ignore_case(string, "LATIN6")
    )
    return CHARSET_ISO_8859_10;
  else if (
    strings_equals_ignore_case(string, "ISO/IEC 8859-11") ||
    strings_equals_ignore_case(string, "ISO-8859-11") ||
    strings_equals_ignore_case(string, "ISO 8859-11") ||
    strings_equals_ignore_case(string, "ISO8859-11") ||
    strings_equals_ignore_case(string, "LATIN/THAI") ||
    strings_equals_ignore_case(string, "LATIN-THAI")
    )
    return CHARSET_ISO_8859_11;
  else if (
    strings_equals_ignore_case(string, "ISO/IEC 8859-12") ||
    strings_equals_ignore_case(string, "ISO-8859-12") ||
    strings_equals_ignore_case(string, "ISO 8859-12") ||
    strings_equals_ignore_case(string, "ISO8859-12")
    )
    return CHARSET_ISO_8859_12;
  else if (
    strings_equals_ignore_case(string, "ISO/IEC 8859-13") ||
    strings_equals_ignore_case(string, "ISO-8859-13") ||
    strings_equals_ignore_case(string, "ISO 8859-13") ||
    strings_equals_ignore_case(string, "ISO8859-13") ||
    strings_equals_ignore_case(string, "LATIN 7") ||
    strings_equals_ignore_case(string, "LATIN-7") ||
    strings_equals_ignore_case(string, "LATIN7")
    )
    return CHARSET_ISO_8859_13;
  else if (
    strings_equals_ignore_case(string, "ISO/IEC 8859-14") ||
    strings_equals_ignore_case(string, "ISO-8859-14") ||
    strings_equals_ignore_case(string, "ISO 8859-14") ||
    strings_equals_ignore_case(string, "ISO8859-14") ||
    strings_equals_ignore_case(string, "LATIN 8") ||
    strings_equals_ignore_case(string, "LATIN-8") ||
    strings_equals_ignore_case(string, "LATIN8")
    )
    return CHARSET_ISO_8859_14;
  else if (
    strings_equals_ignore_case(string, "ISO/IEC 8859-15") ||
    strings_equals_ignore_case(string, "ISO-8859-15") ||
    strings_equals_ignore_case(string, "ISO 8859-15") ||
    strings_equals_ignore_case(string, "ISO8859-15") ||
    strings_equals_ignore_case(string, "LATIN 9") ||
    strings_equals_ignore_case(string, "LATIN-9") ||
    strings_equals_ignore_case(string, "LATIN9") ||
    strings_equals_ignore_case(string, "LATIN 0") ||
    strings_equals_ignore_case(string, "LATIN-0") ||
    strings_equals_ignore_case(string, "LATIN0")
    )
    return CHARSET_ISO_8859_15;
  else if (
    strings_equals_ignore_case(string, "ISO/IEC 8859-16") ||
    strings_equals_ignore_case(string, "ISO-8859-16") ||
    strings_equals_ignore_case(string, "ISO 8859-16") ||
    strings_equals_ignore_case(string, "ISO8859-16") ||
    strings_equals_ignore_case(string, "LATIN 10") ||
    strings_equals_ignore_case(string, "LATIN-10") ||
    strings_equals_ignore_case(string, "LATIN10")
    )
    return CHARSET_ISO_8859_16;
  else
    return CHARSET_NONE;
}

char * charset_to_string(Charset type)
{

  switch (type)
  {
    case CHARSET_ASCII:
      return "US-ASCII";
    case CHARSET_UTF1:
      return "UTF-1";
    case CHARSET_UTF7:
      return "UTF-7";
    case CHARSET_UTF8:
      return "UTF-8";
    case CHARSET_UTF16:
      return "UTF-16";
    case CHARSET_UTF16BE:
      return "UTF-16BE";
    case CHARSET_UTF16LE:
      return "UTF-16LE";
    case CHARSET_UTF32:
      return "UTF-32";
    case CHARSET_UTF32BE:
      return "UTF-32BE";
    case CHARSET_UTF32LE:
      return "UTF-32LE";
    case CHARSET_UTF9:
      return "UTF-9";
    case CHARSET_UTF18:
      return "UTF-18";
    case CHARSET_UTF18BE:
      return "UTF-18BE";
    case CHARSET_UTF18LE:
      return "UTF-18LE";

    case CHARSET_ISO_8859_1:
      return "ISO-8859-1";
    case CHARSET_ISO_8859_2:
      return "ISO-8859-2";
    case CHARSET_ISO_8859_3:
      return "ISO-8859-3";
    case CHARSET_ISO_8859_4:
      return "ISO-8859-4";
    case CHARSET_ISO_8859_5:
      return "ISO-8859-5";
    case CHARSET_ISO_8859_6:
      return "ISO-8859-6";
    case CHARSET_ISO_8859_7:
      return "ISO-8859-7";
    case CHARSET_ISO_8859_8:
      return "ISO-8859-8";
    case CHARSET_ISO_8859_9:
      return "ISO-8859-9";
    case CHARSET_ISO_8859_10:
      return "ISO-8859-10";
    case CHARSET_ISO_8859_11:
      return "ISO-8859-11";
    case CHARSET_ISO_8859_12:
      return "ISO-8859-12";
    case CHARSET_ISO_8859_13:
      return "ISO-8859-13";
    case CHARSET_ISO_8859_14:
      return "ISO-8859-14";
    case CHARSET_ISO_8859_15:
      return "ISO-8859-15";
    case CHARSET_ISO_8859_16:
      return "ISO-8859-16";

    default:
      return CHARSET_NONE;

  }

}
