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

#include "unicode_encoding_type.h"
#include "strings.h"

UnicodeEncodingType unicode_parse_encoding_type(char * string)
{
  assert(string);

  if (
    strings_equals_ignore_case(string, "UTF-1") ||
    strings_equals_ignore_case(string, "UTF1")
    )
    return UNICODE_ENCODING_TYPE_UTF1;
  else if (
    strings_equals_ignore_case(string, "UTF-7") ||
    strings_equals_ignore_case(string, "UTF7")
    )
    return UNICODE_ENCODING_TYPE_UTF7;
  else if (
    strings_equals_ignore_case(string, "UTF-8") ||
    strings_equals_ignore_case(string, "UTF8")
    )
    return UNICODE_ENCODING_TYPE_UTF8;
  else if (
    strings_equals_ignore_case(string, "UTF-16") ||
    strings_equals_ignore_case(string, "UTF16")
    )
    return UNICODE_ENCODING_TYPE_UTF16;
  else if (
    strings_equals_ignore_case(string, "UTF-16BE") ||
    strings_equals_ignore_case(string, "UTF16BE")
    )
    return UNICODE_ENCODING_TYPE_UTF16BE;
  else if (
    strings_equals_ignore_case(string, "UTF-16LE") ||
    strings_equals_ignore_case(string, "UTF16LE")
    )
    return UNICODE_ENCODING_TYPE_UTF16LE;
  else if (
    strings_equals_ignore_case(string, "UTF-32") ||
    strings_equals_ignore_case(string, "UTF32")
    )
    return UNICODE_ENCODING_TYPE_UTF32;
  else if (
    strings_equals_ignore_case(string, "UTF-32BE") ||
    strings_equals_ignore_case(string, "UTF32BE")
    )
    return UNICODE_ENCODING_TYPE_UTF32BE;
  else if (
    strings_equals_ignore_case(string, "UTF-32LE") ||
    strings_equals_ignore_case(string, "UTF32LE")
    )
    return UNICODE_ENCODING_TYPE_UTF32LE;
  else if (
    strings_equals_ignore_case(string, "UTF-9") ||
    strings_equals_ignore_case(string, "UTF9")
    )
    return UNICODE_ENCODING_TYPE_UTF9;
  else if (
    strings_equals_ignore_case(string, "UTF-18") ||
    strings_equals_ignore_case(string, "UTF18")
    )
    return UNICODE_ENCODING_TYPE_UTF18;
  else if (
    strings_equals_ignore_case(string, "UTF-18BE") ||
    strings_equals_ignore_case(string, "UTF18BE")
    )
    return UNICODE_ENCODING_TYPE_UTF18BE;
  else if (
    strings_equals_ignore_case(string, "UTF-18LE") ||
    strings_equals_ignore_case(string, "UTF18LE")
    )
    return UNICODE_ENCODING_TYPE_UTF18LE;

  else
    return UNICODE_ENCODING_TYPE_NONE;

}

char * unicode_encoding_type_to_string(UnicodeEncodingType type)
{

  switch (type)
  {
    case UNICODE_ENCODING_TYPE_UTF1:
      return "UTF-1";
    case UNICODE_ENCODING_TYPE_UTF7:
      return "UTF-7";
    case UNICODE_ENCODING_TYPE_UTF8:
      return "UTF-8";
    case UNICODE_ENCODING_TYPE_UTF16:
      return "UTF-16";
    case UNICODE_ENCODING_TYPE_UTF16BE:
      return "UTF-16BE";
    case UNICODE_ENCODING_TYPE_UTF16LE:
      return "UTF-16LE";
    case UNICODE_ENCODING_TYPE_UTF32:
      return "UTF-32";
    case UNICODE_ENCODING_TYPE_UTF32BE:
      return "UTF-32BE";
    case UNICODE_ENCODING_TYPE_UTF32LE:
      return "UTF-32LE";
    case UNICODE_ENCODING_TYPE_UTF9:
      return "UTF-9";
    case UNICODE_ENCODING_TYPE_UTF18:
      return "UTF-18";
    case UNICODE_ENCODING_TYPE_UTF18BE:
      return "UTF-18BE";
    case UNICODE_ENCODING_TYPE_UTF18LE:
      return "UTF-18LE";

    default:
      return UNICODE_ENCODING_TYPE_NONE;

  }

}
