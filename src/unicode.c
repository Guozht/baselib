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
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "charset.h"
#include "strings.h"
#include "endianness.h"

#include "unicode.h"

/** UNICODE **/



char * unicode_get_block_name(uint32_t code_point)
{
  if (code_point >= 0x0000 && code_point <= 0x007F)
    return "Basic Latin";
  else if (code_point >= 0x0080 && code_point <= 0x00FF)
    return "Latin-1 Supplement";
  else if (code_point >= 0x0100 && code_point <= 0x017F)
    return "Latin Extended-A";
  else if (code_point >= 0x0180 && code_point <= 0x024F)
    return "Latin Extended-B";
  else if (code_point >= 0x0250 && code_point <= 0x02AF)
    return "IPA Extensions";
  else if (code_point >= 0x02B0 && code_point <= 0x02FF)
    return "Spacing Modifier Letters";
  else if (code_point >= 0x0300 && code_point <= 0x036F)
    return "Combining Diacritical Marks";
  else if (code_point >= 0x0370 && code_point <= 0x03FF)
    return "Greek and Coptic";
  else if (code_point >= 0x0400 && code_point <= 0x04FF)
    return "Cyrillic";
  else if (code_point >= 0x0500 && code_point <= 0x052F)
    return "Cyrillic Supplement";
  else if (code_point >= 0x0530 && code_point <= 0x058F)
    return "Armenian";
  else if (code_point >= 0x0590 && code_point <= 0x05FF)
    return "Hebrew";
  else if (code_point >= 0x0600 && code_point <= 0x06FF)
    return "Arabic";
  else if (code_point >= 0x0700 && code_point <= 0x074F)
    return "Syriac";
  else if (code_point >= 0x0750 && code_point <= 0x077F)
    return "Arabic Supplement";
  else if (code_point >= 0x0780 && code_point <= 0x07BF)
    return "Thaana";
  else if (code_point >= 0x07C0 && code_point <= 0x07FF)
    return "NKo";
  else if (code_point >= 0x0800 && code_point <= 0x083F)
    return "Samaritan";
  else if (code_point >= 0x0840 && code_point <= 0x085F)
    return "Mandaic";
  else if (code_point >= 0x0860 && code_point <= 0x086F)
    return "Syriac Supplement";
  else if (code_point >= 0x08A0 && code_point <= 0x08FF)
    return "Arabic Extended-A";
  else if (code_point >= 0x0900 && code_point <= 0x097F)
    return "Devanagari";
  else if (code_point >= 0x0980 && code_point <= 0x09FF)
    return "Bengali";
  else if (code_point >= 0x0A00 && code_point <= 0x0A7F)
    return "Gurmukhi";
  else if (code_point >= 0x0A80 && code_point <= 0x0AFF)
    return "Gujarati";
  else if (code_point >= 0x0B00 && code_point <= 0x0B7F)
    return "Oriya";
  else if (code_point >= 0x0B80 && code_point <= 0x0BFF)
    return "Tamil";
  else if (code_point >= 0x0C00 && code_point <= 0x0C7F)
    return "Telugu";
  else if (code_point >= 0x0C80 && code_point <= 0x0CFF)
    return "Kannada";
  else if (code_point >= 0x0D00 && code_point <= 0x0D7F)
    return "Malayalam";
  else if (code_point >= 0x0D80 && code_point <= 0x0DFF)
    return "Sinhala";
  else if (code_point >= 0x0E00 && code_point <= 0x0E7F)
    return "Thai";
  else if (code_point >= 0x0E80 && code_point <= 0x0EFF)
    return "Lao";
  else if (code_point >= 0x0F00 && code_point <= 0x0FFF)
    return "Tibetan";
  else if (code_point >= 0x1000 && code_point <= 0x109F)
    return "Myanmar";
  else if (code_point >= 0x10A0 && code_point <= 0x10FF)
    return "Georgian";
  else if (code_point >= 0x1100 && code_point <= 0x11FF)
    return "Hangul Jamo";
  else if (code_point >= 0x1200 && code_point <= 0x137F)
    return "Ethiopic";
  else if (code_point >= 0x1380 && code_point <= 0x139F)
    return "Ethiopic Supplement";
  else if (code_point >= 0x13A0 && code_point <= 0x13FF)
    return "Cherokee";
  else if (code_point >= 0x1400 && code_point <= 0x167F)
    return "Unified Canadian Aboriginal Syllabics";
  else if (code_point >= 0x1680 && code_point <= 0x169F)
    return "Ogham";
  else if (code_point >= 0x16A0 && code_point <= 0x16FF)
    return "Runic";
  else if (code_point >= 0x1700 && code_point <= 0x171F)
    return "Tagalog";
  else if (code_point >= 0x1720 && code_point <= 0x173F)
    return "Hanunoo";
  else if (code_point >= 0x1740 && code_point <= 0x175F)
    return "Buhid";
  else if (code_point >= 0x1760 && code_point <= 0x177F)
    return "Tagbanwa";
  else if (code_point >= 0x1780 && code_point <= 0x17FF)
    return "Khmer";
  else if (code_point >= 0x1800 && code_point <= 0x18AF)
    return "Mongolian";
  else if (code_point >= 0x18B0 && code_point <= 0x18FF)
    return "Unified Canadian Aboriginal Syllabics Extended";
  else if (code_point >= 0x1900 && code_point <= 0x194F)
    return "Limbu";
  else if (code_point >= 0x1950 && code_point <= 0x197F)
    return "Tai Le";
  else if (code_point >= 0x1980 && code_point <= 0x19DF)
    return "New Tai Lue";
  else if (code_point >= 0x19E0 && code_point <= 0x19FF)
    return "Khmer Symbols";
  else if (code_point >= 0x1A00 && code_point <= 0x1A1F)
    return "Buginese";
  else if (code_point >= 0x1A20 && code_point <= 0x1AAF)
    return "Tai Tham";
  else if (code_point >= 0x1AB0 && code_point <= 0x1AFF)
    return "Combining Diacritical Marks Extended";
  else if (code_point >= 0x1B00 && code_point <= 0x1B7F)
    return "Balinese";
  else if (code_point >= 0x1B80 && code_point <= 0x1BBF)
    return "Sundanese";
  else if (code_point >= 0x1BC0 && code_point <= 0x1BFF)
    return "Batak";
  else if (code_point >= 0x1C00 && code_point <= 0x1C4F)
    return "Lepcha";
  else if (code_point >= 0x1C50 && code_point <= 0x1C7F)
    return "Ol Chiki";
  else if (code_point >= 0x1C80 && code_point <= 0x1C8F)
    return "Cyrillic Extended-C";
  else if (code_point >= 0x1CC0 && code_point <= 0x1CCF)
    return "Sundanese Supplement";
  else if (code_point >= 0x1CD0 && code_point <= 0x1CFF)
    return "Vedic Extensions";
  else if (code_point >= 0x1D00 && code_point <= 0x1D7F)
    return "Phonetic Extensions";
  else if (code_point >= 0x1D80 && code_point <= 0x1DBF)
    return "Phonetic Extensions Supplement";
  else if (code_point >= 0x1DC0 && code_point <= 0x1DFF)
    return "Combining Diacritical Marks Supplement";
  else if (code_point >= 0x1E00 && code_point <= 0x1EFF)
    return "Latin Extended Additional";
  else if (code_point >= 0x1F00 && code_point <= 0x1FFF)
    return "Greek Extended";
  else if (code_point >= 0x2000 && code_point <= 0x206F)
    return "General Punctuation";
  else if (code_point >= 0x2070 && code_point <= 0x209F)
    return "Superscripts and Subscripts";
  else if (code_point >= 0x20A0 && code_point <= 0x20CF)
    return "Currency Symbols";
  else if (code_point >= 0x20D0 && code_point <= 0x20FF)
    return "Combining Diacritical Marks for Symbols";
  else if (code_point >= 0x2100 && code_point <= 0x214F)
    return "Letterlike Symbols";
  else if (code_point >= 0x2150 && code_point <= 0x218F)
    return "Number Forms";
  else if (code_point >= 0x2190 && code_point <= 0x21FF)
    return "Arrows";
  else if (code_point >= 0x2200 && code_point <= 0x22FF)
    return "Mathematical Operators";
  else if (code_point >= 0x2300 && code_point <= 0x23FF)
    return "Miscellaneous Technical";
  else if (code_point >= 0x2400 && code_point <= 0x243F)
    return "Control Pictures";
  else if (code_point >= 0x2440 && code_point <= 0x245F)
    return "Optical Character Recognition";
  else if (code_point >= 0x2460 && code_point <= 0x24FF)
    return "Enclosed Alphanumerics";
  else if (code_point >= 0x2500 && code_point <= 0x257F)
    return "Box Drawing";
  else if (code_point >= 0x2580 && code_point <= 0x259F)
    return "Block Elements";
  else if (code_point >= 0x25A0 && code_point <= 0x25FF)
    return "Geometric Shapes";
  else if (code_point >= 0x2600 && code_point <= 0x26FF)
    return "Miscellaneous Symbols";
  else if (code_point >= 0x2700 && code_point <= 0x27BF)
    return "Dingbats";
  else if (code_point >= 0x27C0 && code_point <= 0x27EF)
    return "Miscellaneous Mathematical Symbols-A";
  else if (code_point >= 0x27F0 && code_point <= 0x27FF)
    return "Supplemental Arrows-A";
  else if (code_point >= 0x2800 && code_point <= 0x28FF)
    return "Braille Patterns";
  else if (code_point >= 0x2900 && code_point <= 0x297F)
    return "Supplemental Arrows-B";
  else if (code_point >= 0x2980 && code_point <= 0x29FF)
    return "Miscellaneous Mathematical Symbols-B";
  else if (code_point >= 0x2A00 && code_point <= 0x2AFF)
    return "Supplemental Mathematical Operators";
  else if (code_point >= 0x2B00 && code_point <= 0x2BFF)
    return "Miscellaneous Symbols and Arrows";
  else if (code_point >= 0x2C00 && code_point <= 0x2C5F)
    return "Glagolitic";
  else if (code_point >= 0x2C60 && code_point <= 0x2C7F)
    return "Latin Extended-C";
  else if (code_point >= 0x2C80 && code_point <= 0x2CFF)
    return "Coptic";
  else if (code_point >= 0x2D00 && code_point <= 0x2D2F)
    return "Georgian Supplement";
  else if (code_point >= 0x2D30 && code_point <= 0x2D7F)
    return "Tifinagh";
  else if (code_point >= 0x2D80 && code_point <= 0x2DDF)
    return "Ethiopic Extended";
  else if (code_point >= 0x2DE0 && code_point <= 0x2DFF)
    return "Cyrillic Extended-A";
  else if (code_point >= 0x2E00 && code_point <= 0x2E7F)
    return "Supplemental Punctuation";
  else if (code_point >= 0x2E80 && code_point <= 0x2EFF)
    return "CJK Radicals Supplement";
  else if (code_point >= 0x2F00 && code_point <= 0x2FDF)
    return "Kangxi Radicals";
  else if (code_point >= 0x2FF0 && code_point <= 0x2FFF)
    return "Ideographic Description Characters";
  else if (code_point >= 0x3000 && code_point <= 0x303F)
    return "CJK Symbols and Punctuation";
  else if (code_point >= 0x3040 && code_point <= 0x309F)
    return "Hiragana";
  else if (code_point >= 0x30A0 && code_point <= 0x30FF)
    return "Katakana";
  else if (code_point >= 0x3100 && code_point <= 0x312F)
    return "Bopomofo";
  else if (code_point >= 0x3130 && code_point <= 0x318F)
    return "Hangul Compatibility Jamo";
  else if (code_point >= 0x3190 && code_point <= 0x319F)
    return "Kanbun";
  else if (code_point >= 0x31A0 && code_point <= 0x31BF)
    return "Bopomofo Extended";
  else if (code_point >= 0x31C0 && code_point <= 0x31EF)
    return "CJK Strokes";
  else if (code_point >= 0x31F0 && code_point <= 0x31FF)
    return "Katakana Phonetic Extensions";
  else if (code_point >= 0x3200 && code_point <= 0x32FF)
    return "Enclosed CJK Letters and Months";
  else if (code_point >= 0x3300 && code_point <= 0x33FF)
    return "CJK Compatibility";
  else if (code_point >= 0x3400 && code_point <= 0x4DBF)
    return "CJK Unified Ideographs Extension A";
  else if (code_point >= 0x4DC0 && code_point <= 0x4DFF)
    return "Yijing Hexagram Symbols";
  else if (code_point >= 0x4E00 && code_point <= 0x9FFF)
    return "CJK Unified Ideographs";
  else if (code_point >= 0xA000 && code_point <= 0xA48F)
    return "Yi Syllables";
  else if (code_point >= 0xA490 && code_point <= 0xA4CF)
    return "Yi Radicals";
  else if (code_point >= 0xA4D0 && code_point <= 0xA4FF)
    return "Lisu";
  else if (code_point >= 0xA500 && code_point <= 0xA63F)
    return "Vai";
  else if (code_point >= 0xA640 && code_point <= 0xA69F)
    return "Cyrillic Extended-B";
  else if (code_point >= 0xA6A0 && code_point <= 0xA6FF)
    return "Bamum";
  else if (code_point >= 0xA700 && code_point <= 0xA71F)
    return "Modifier Tone Letters";
  else if (code_point >= 0xA720 && code_point <= 0xA7FF)
    return "Latin Extended-D";
  else if (code_point >= 0xA800 && code_point <= 0xA82F)
    return "Syloti Nagri";
  else if (code_point >= 0xA830 && code_point <= 0xA83F)
    return "Common Indic Number Forms";
  else if (code_point >= 0xA840 && code_point <= 0xA87F)
    return "Phags-pa";
  else if (code_point >= 0xA880 && code_point <= 0xA8DF)
    return "Saurashtra";
  else if (code_point >= 0xA8E0 && code_point <= 0xA8FF)
    return "Devanagari Extended";
  else if (code_point >= 0xA900 && code_point <= 0xA92F)
    return "Kayah Li";
  else if (code_point >= 0xA930 && code_point <= 0xA95F)
    return "Rejang";
  else if (code_point >= 0xA960 && code_point <= 0xA97F)
    return "Hangul Jamo Extended-A";
  else if (code_point >= 0xA980 && code_point <= 0xA9DF)
    return "Javanese";
  else if (code_point >= 0xA9E0 && code_point <= 0xA9FF)
    return "Myanmar Extended-B";
  else if (code_point >= 0xAA00 && code_point <= 0xAA5F)
    return "Cham";
  else if (code_point >= 0xAA60 && code_point <= 0xAA7F)
    return "Myanmar Extended-A";
  else if (code_point >= 0xAA80 && code_point <= 0xAADF)
    return "Tai Viet";
  else if (code_point >= 0xAAE0 && code_point <= 0xAAFF)
    return "Meetei Mayek Extensions";
  else if (code_point >= 0xAB00 && code_point <= 0xAB2F)
    return "Ethiopic Extended-A";
  else if (code_point >= 0xAB30 && code_point <= 0xAB6F)
    return "Latin Extended-E";
  else if (code_point >= 0xAB70 && code_point <= 0xABBF)
    return "Cherokee Supplement";
  else if (code_point >= 0xABC0 && code_point <= 0xABFF)
    return "Meetei Mayek";
  else if (code_point >= 0xAC00 && code_point <= 0xD7AF)
    return "Hangul Syllables";
  else if (code_point >= 0xD7B0 && code_point <= 0xD7FF)
    return "Hangul Jamo Extended-B";
  else if (code_point >= 0xD800 && code_point <= 0xDB7F)
    return "High Surrogates";
  else if (code_point >= 0xDB80 && code_point <= 0xDBFF)
    return "High Private Use Surrogates";
  else if (code_point >= 0xDC00 && code_point <= 0xDFFF)
    return "Low Surrogates";
  else if (code_point >= 0xE000 && code_point <= 0xF8FF)
    return "Private Use Area";
  else if (code_point >= 0xF900 && code_point <= 0xFAFF)
    return "CJK Compatibility Ideographs";
  else if (code_point >= 0xFB00 && code_point <= 0xFB4F)
    return "Alphabetic Presentation Forms";
  else if (code_point >= 0xFB50 && code_point <= 0xFDFF)
    return "Arabic Presentation Forms-A";
  else if (code_point >= 0xFE00 && code_point <= 0xFE0F)
    return "Variation Selectors";
  else if (code_point >= 0xFE10 && code_point <= 0xFE1F)
    return "Vertical Forms";
  else if (code_point >= 0xFE20 && code_point <= 0xFE2F)
    return "Combining Half Marks";
  else if (code_point >= 0xFE30 && code_point <= 0xFE4F)
    return "CJK Compatibility Forms";
  else if (code_point >= 0xFE50 && code_point <= 0xFE6F)
    return "Small Form Variants";
  else if (code_point >= 0xFE70 && code_point <= 0xFEFF)
    return "Arabic Presentation Forms-B";
  else if (code_point >= 0xFF00 && code_point <= 0xFFEF)
    return "Halfwidth and Fullwidth Forms";
  else if (code_point >= 0xFFF0 && code_point <= 0xFFFF)
    return "Specials";
  else if (code_point >= 0x10000 && code_point <= 0x1007F)
    return "Linear B Syllabary";
  else if (code_point >= 0x10080 && code_point <= 0x100FF)
    return "Linear B Ideograms";
  else if (code_point >= 0x10100 && code_point <= 0x1013F)
    return "Aegean Numbers";
  else if (code_point >= 0x10140 && code_point <= 0x1018F)
    return "Ancient Greek Numbers";
  else if (code_point >= 0x10190 && code_point <= 0x101CF)
    return "Ancient Symbols";
  else if (code_point >= 0x101D0 && code_point <= 0x101FF)
    return "Phaistos Disc";
  else if (code_point >= 0x10280 && code_point <= 0x1029F)
    return "Lycian";
  else if (code_point >= 0x102A0 && code_point <= 0x102DF)
    return "Carian";
  else if (code_point >= 0x102E0 && code_point <= 0x102FF)
    return "Coptic Epact Numbers";
  else if (code_point >= 0x10300 && code_point <= 0x1032F)
    return "Old Italic";
  else if (code_point >= 0x10330 && code_point <= 0x1034F)
    return "Gothic";
  else if (code_point >= 0x10350 && code_point <= 0x1037F)
    return "Old Permic";
  else if (code_point >= 0x10380 && code_point <= 0x1039F)
    return "Ugaritic";
  else if (code_point >= 0x103A0 && code_point <= 0x103DF)
    return "Old Persian";
  else if (code_point >= 0x10400 && code_point <= 0x1044F)
    return "Deseret";
  else if (code_point >= 0x10450 && code_point <= 0x1047F)
    return "Shavian";
  else if (code_point >= 0x10480 && code_point <= 0x104AF)
    return "Osmanya";
  else if (code_point >= 0x104B0 && code_point <= 0x104FF)
    return "Osage";
  else if (code_point >= 0x10500 && code_point <= 0x1052F)
    return "Elbasan";
  else if (code_point >= 0x10530 && code_point <= 0x1056F)
    return "Caucasian Albanian";
  else if (code_point >= 0x10600 && code_point <= 0x1077F)
    return "Linear A";
  else if (code_point >= 0x10800 && code_point <= 0x1083F)
    return "Cypriot Syllabary";
  else if (code_point >= 0x10840 && code_point <= 0x1085F)
    return "Imperial Aramaic";
  else if (code_point >= 0x10860 && code_point <= 0x1087F)
    return "Palmyrene";
  else if (code_point >= 0x10880 && code_point <= 0x108AF)
    return "Nabataean";
  else if (code_point >= 0x108E0 && code_point <= 0x108FF)
    return "Hatran";
  else if (code_point >= 0x10900 && code_point <= 0x1091F)
    return "Phoenician";
  else if (code_point >= 0x10920 && code_point <= 0x1093F)
    return "Lydian";
  else if (code_point >= 0x10980 && code_point <= 0x1099F)
    return "Meroitic Hieroglyphs";
  else if (code_point >= 0x109A0 && code_point <= 0x109FF)
    return "Meroitic Cursive";
  else if (code_point >= 0x10A00 && code_point <= 0x10A5F)
    return "Kharoshthi";
  else if (code_point >= 0x10A60 && code_point <= 0x10A7F)
    return "Old South Arabian";
  else if (code_point >= 0x10A80 && code_point <= 0x10A9F)
    return "Old North Arabian";
  else if (code_point >= 0x10AC0 && code_point <= 0x10AFF)
    return "Manichaean";
  else if (code_point >= 0x10B00 && code_point <= 0x10B3F)
    return "Avestan";
  else if (code_point >= 0x10B40 && code_point <= 0x10B5F)
    return "Inscriptional Parthian";
  else if (code_point >= 0x10B60 && code_point <= 0x10B7F)
    return "Inscriptional Pahlavi";
  else if (code_point >= 0x10B80 && code_point <= 0x10BAF)
    return "Psalter Pahlavi";
  else if (code_point >= 0x10C00 && code_point <= 0x10C4F)
    return "Old Turkic";
  else if (code_point >= 0x10C80 && code_point <= 0x10CFF)
    return "Old Hungarian";
  else if (code_point >= 0x10E60 && code_point <= 0x10E7F)
    return "Rumi Numeral Symbols";
  else if (code_point >= 0x11000 && code_point <= 0x1107F)
    return "Brahmi";
  else if (code_point >= 0x11080 && code_point <= 0x110CF)
    return "Kaithi";
  else if (code_point >= 0x110D0 && code_point <= 0x110FF)
    return "Sora Sompeng";
  else if (code_point >= 0x11100 && code_point <= 0x1114F)
    return "Chakma";
  else if (code_point >= 0x11150 && code_point <= 0x1117F)
    return "Mahajani";
  else if (code_point >= 0x11180 && code_point <= 0x111DF)
    return "Sharada";
  else if (code_point >= 0x111E0 && code_point <= 0x111FF)
    return "Sinhala Archaic Numbers";
  else if (code_point >= 0x11200 && code_point <= 0x1124F)
    return "Khojki";
  else if (code_point >= 0x11280 && code_point <= 0x112AF)
    return "Multani";
  else if (code_point >= 0x112B0 && code_point <= 0x112FF)
    return "Khudawadi";
  else if (code_point >= 0x11300 && code_point <= 0x1137F)
    return "Grantha";
  else if (code_point >= 0x11400 && code_point <= 0x1147F)
    return "Newa";
  else if (code_point >= 0x11480 && code_point <= 0x114DF)
    return "Tirhuta";
  else if (code_point >= 0x11580 && code_point <= 0x115FF)
    return "Siddham";
  else if (code_point >= 0x11600 && code_point <= 0x1165F)
    return "Modi";
  else if (code_point >= 0x11660 && code_point <= 0x1167F)
    return "Mongolian Supplement";
  else if (code_point >= 0x11680 && code_point <= 0x116CF)
    return "Takri";
  else if (code_point >= 0x11700 && code_point <= 0x1173F)
    return "Ahom";
  else if (code_point >= 0x118A0 && code_point <= 0x118FF)
    return "Warang Citi";
  else if (code_point >= 0x11A00 && code_point <= 0x11A4F)
    return "Zanabazar Square";
  else if (code_point >= 0x11A50 && code_point <= 0x11AAF)
    return "Soyombo";
  else if (code_point >= 0x11AC0 && code_point <= 0x11AFF)
    return "Pau Cin Hau";
  else if (code_point >= 0x11C00 && code_point <= 0x11C6F)
    return "Bhaiksuki";
  else if (code_point >= 0x11C70 && code_point <= 0x11CBF)
    return "Marchen";
  else if (code_point >= 0x11D00 && code_point <= 0x11D5F)
    return "Masaram Gondi";
  else if (code_point >= 0x12000 && code_point <= 0x123FF)
    return "Cuneiform";
  else if (code_point >= 0x12400 && code_point <= 0x1247F)
    return "Cuneiform Numbers and Punctuation";
  else if (code_point >= 0x12480 && code_point <= 0x1254F)
    return "Early Dynastic Cuneiform";
  else if (code_point >= 0x13000 && code_point <= 0x1342F)
    return "Egyptian Hieroglyphs";
  else if (code_point >= 0x14400 && code_point <= 0x1467F)
    return "Anatolian Hieroglyphs";
  else if (code_point >= 0x16800 && code_point <= 0x16A3F)
    return "Bamum Supplement";
  else if (code_point >= 0x16A40 && code_point <= 0x16A6F)
    return "Mro";
  else if (code_point >= 0x16AD0 && code_point <= 0x16AFF)
    return "Bassa Vah";
  else if (code_point >= 0x16B00 && code_point <= 0x16B8F)
    return "Pahawh Hmong";
  else if (code_point >= 0x16F00 && code_point <= 0x16F9F)
    return "Miao";
  else if (code_point >= 0x16FE0 && code_point <= 0x16FFF)
    return "Ideographic Symbols and Punctuation";
  else if (code_point >= 0x17000 && code_point <= 0x187FF)
    return "Tangut";
  else if (code_point >= 0x18800 && code_point <= 0x18AFF)
    return "Tangut Components";
  else if (code_point >= 0x1B000 && code_point <= 0x1B0FF)
    return "Kana Supplement";
  else if (code_point >= 0x1B100 && code_point <= 0x1B12F)
    return "Kana Extended-A";
  else if (code_point >= 0x1B170 && code_point <= 0x1B2FF)
    return "Nushu";
  else if (code_point >= 0x1BC00 && code_point <= 0x1BC9F)
    return "Duployan";
  else if (code_point >= 0x1BCA0 && code_point <= 0x1BCAF)
    return "Shorthand Format Controls";
  else if (code_point >= 0x1D000 && code_point <= 0x1D0FF)
    return "Byzantine Musical Symbols";
  else if (code_point >= 0x1D100 && code_point <= 0x1D1FF)
    return "Musical Symbols";
  else if (code_point >= 0x1D200 && code_point <= 0x1D24F)
    return "Ancient Greek Musical Notation";
  else if (code_point >= 0x1D300 && code_point <= 0x1D35F)
    return "Tai Xuan Jing Symbols";
  else if (code_point >= 0x1D360 && code_point <= 0x1D37F)
    return "Counting Rod Numerals";
  else if (code_point >= 0x1D400 && code_point <= 0x1D7FF)
    return "Mathematical Alphanumeric Symbols";
  else if (code_point >= 0x1D800 && code_point <= 0x1DAAF)
    return "Sutton SignWriting";
  else if (code_point >= 0x1E000 && code_point <= 0x1E02F)
    return "Glagolitic Supplement";
  else if (code_point >= 0x1E800 && code_point <= 0x1E8DF)
    return "Mende Kikakui";
  else if (code_point >= 0x1E900 && code_point <= 0x1E95F)
    return "Adlam";
  else if (code_point >= 0x1EE00 && code_point <= 0x1EEFF)
    return "Arabic Mathematical Alphabetic Symbols";
  else if (code_point >= 0x1F000 && code_point <= 0x1F02F)
    return "Mahjong Tiles";
  else if (code_point >= 0x1F030 && code_point <= 0x1F09F)
    return "Domino Tiles";
  else if (code_point >= 0x1F0A0 && code_point <= 0x1F0FF)
    return "Playing Cards";
  else if (code_point >= 0x1F100 && code_point <= 0x1F1FF)
    return "Enclosed Alphanumeric Supplement";
  else if (code_point >= 0x1F200 && code_point <= 0x1F2FF)
    return "Enclosed Ideographic Supplement";
  else if (code_point >= 0x1F300 && code_point <= 0x1F5FF)
    return "Miscellaneous Symbols and Pictographs";
  else if (code_point >= 0x1F600 && code_point <= 0x1F64F)
    return "Emoticons";
  else if (code_point >= 0x1F650 && code_point <= 0x1F67F)
    return "Ornamental Dingbats";
  else if (code_point >= 0x1F680 && code_point <= 0x1F6FF)
    return "Transport and Map Symbols";
  else if (code_point >= 0x1F700 && code_point <= 0x1F77F)
    return "Alchemical Symbols";
  else if (code_point >= 0x1F780 && code_point <= 0x1F7FF)
    return "Geometric Shapes Extended";
  else if (code_point >= 0x1F800 && code_point <= 0x1F8FF)
    return "Supplemental Arrows-C";
  else if (code_point >= 0x1F900 && code_point <= 0x1F9FF)
    return "Supplemental Symbols and Pictographs";
  else if (code_point >= 0x20000 && code_point <= 0x2A6DF)
    return "CJK Unified Ideographs Extension B";
  else if (code_point >= 0x2A700 && code_point <= 0x2B73F)
    return "CJK Unified Ideographs Extension C";
  else if (code_point >= 0x2B740 && code_point <= 0x2B81F)
    return "CJK Unified Ideographs Extension D";
  else if (code_point >= 0x2B820 && code_point <= 0x2CEAF)
    return "CJK Unified Ideographs Extension E";
  else if (code_point >= 0x2CEB0 && code_point <= 0x2EBEF)
    return "CJK Unified Ideographs Extension F";
  else if (code_point >= 0x2F800 && code_point <= 0x2FA1F)
    return "CJK Compatibility Ideographs Supplement";
  else if (code_point >= 0xE0000 && code_point <= 0xE007F)
    return "Tags";
  else if (code_point >= 0xE0100 && code_point <= 0xE01EF)
    return "Variation Selectors Supplement";
  else if (code_point >= 0xF0000 && code_point <= 0xFFFFF)
    return "Supplementary Private Use Area-A";
  else if (code_point >= 0x100000 && code_point <= 0x10FFFF)
    return "Supplementary Private Use Area-B";
  else
    return "Unknown";
}

bool unicode_is_valid_code_point(uint32_t code_point)
{
  return
    code_point <= 0x10FFFF &&
    code_point != 0xFFFE &&
    !(code_point >= 0xD800 && code_point <= 0xDFFF)
    ;
}


/** GENERIC **/


unsigned int unicode_code_point_byte_requirement(Charset encoding, uint32_t code_point)
{
  switch (encoding)
  {
    case CHARSET_UTF7:
      return unicode_code_point_byte_requirement_utf7(code_point);
    case CHARSET_UTF8:
      return unicode_code_point_byte_requirement_utf8(code_point);
    case CHARSET_UTF16:
    case CHARSET_UTF16BE:
    case CHARSET_UTF16LE:
      return unicode_code_point_byte_requirement_utf16(code_point);
    case CHARSET_UTF32:
    case CHARSET_UTF32BE:
    case CHARSET_UTF32LE:
      return unicode_code_point_byte_requirement_utf32(code_point);
      
    case CHARSET_UTF1:
    case CHARSET_UTF9:
    case CHARSET_UTF18:
    case CHARSET_UTF18BE:
    case CHARSET_UTF18LE:
      assert(0); /* NOT YET IMPLEMENTED */
      
    default:
      assert(0);
  }
}

bool unicode_is_well_formed(Charset encoding, char * string, size_t string_length)
{
  switch (encoding)
  {
    case CHARSET_UTF7:
      return unicode_is_well_formed_utf7(string, string_length);
    case CHARSET_UTF8:
      return unicode_is_well_formed_utf8(string, string_length);
    case CHARSET_UTF16:
      return unicode_is_well_formed_utf16(string, string_length);
    case CHARSET_UTF16BE:
      return unicode_is_well_formed_utf16be(string, string_length);
    case CHARSET_UTF16LE:
      return unicode_is_well_formed_utf16le(string, string_length);
    case CHARSET_UTF32:
      return unicode_is_well_formed_utf32(string, string_length);
    case CHARSET_UTF32BE:
      return unicode_is_well_formed_utf32be(string, string_length);
    case CHARSET_UTF32LE:
      return unicode_is_well_formed_utf32le(string, string_length);
      
    case CHARSET_UTF1:
    case CHARSET_UTF9:
    case CHARSET_UTF18:
    case CHARSET_UTF18BE:
    case CHARSET_UTF18LE:
      assert(0); /* NOT YET IMPLEMENTED */
      
    default:
      assert(0);
  }
}

unsigned int unicode_string_length(Charset encoding, char * string, size_t string_length)
{
  switch (encoding)
  {
    case CHARSET_UTF7:
      return unicode_string_length_utf7(string, string_length);
    case CHARSET_UTF8:
      return unicode_string_length_utf8(string, string_length);
    case CHARSET_UTF16:
      return unicode_string_length_utf16(string, string_length);
    case CHARSET_UTF16BE:
      return unicode_string_length_utf16be(string, string_length);
    case CHARSET_UTF16LE:
      return unicode_string_length_utf16le(string, string_length);
    case CHARSET_UTF32:
      return unicode_string_length_utf32(string, string_length);
    case CHARSET_UTF32BE:
      return unicode_string_length_utf32be(string, string_length);
    case CHARSET_UTF32LE:
      return unicode_string_length_utf32le(string, string_length);
      
    case CHARSET_UTF1:
    case CHARSET_UTF9:
    case CHARSET_UTF18:
    case CHARSET_UTF18BE:
    case CHARSET_UTF18LE:
      assert(0); /* NOT YET IMPLEMENTED */
      
    default:
      assert(0);
  }
}

int unicode_read(Charset encoding, char * string, uint32_t * code_point)
{
  switch (encoding)
  {
    case CHARSET_UTF7:
      return unicode_read_utf7(string, code_point);
    case CHARSET_UTF8:
      return unicode_read_utf8(string, code_point);
    case CHARSET_UTF16:
      assert(0); /* CANNOT READ WITHOUT BYTE ORDER */
    case CHARSET_UTF16BE:
      return unicode_read_utf16be(string, code_point);
    case CHARSET_UTF16LE:
      return unicode_read_utf16le(string, code_point);
    case CHARSET_UTF32:
      assert(0); /* CANNOT READ WITHOUT BYTE ORDER */
    case CHARSET_UTF32BE:
      return unicode_read_utf32be(string, code_point);
    case CHARSET_UTF32LE:
      return unicode_read_utf32le(string, code_point);
      
    case CHARSET_UTF1:
    case CHARSET_UTF9:
    case CHARSET_UTF18:
    case CHARSET_UTF18BE:
    case CHARSET_UTF18LE:
      assert(0); /* NOT YET IMPLEMENTED */
      
    default:
      assert(0);
  }
}

int unicode_write(Charset encoding, uint32_t code_point, char * string)
{
  switch (encoding)
  {
    case CHARSET_UTF7:
      return unicode_write_utf7(code_point, string);
    case CHARSET_UTF8:
      return unicode_write_utf8(code_point, string);
    case CHARSET_UTF16:
      return unicode_write_utf16(code_point, string);
    case CHARSET_UTF16BE:
      return unicode_write_utf16be(code_point, string);
    case CHARSET_UTF16LE:
      return unicode_write_utf16le(code_point, string);
    case CHARSET_UTF32:
      return unicode_write_utf32(code_point, string);
    case CHARSET_UTF32BE:
      return unicode_write_utf32be(code_point, string);
    case CHARSET_UTF32LE:
      return unicode_write_utf32le(code_point, string);
      
    case CHARSET_UTF1:
    case CHARSET_UTF9:
    case CHARSET_UTF18:
    case CHARSET_UTF18BE:
    case CHARSET_UTF18LE:
      assert(0); /* NOT YET IMPLEMENTED */
      
    default:
      assert(0);
  }
}

uint32_t * unicode_read_string(Charset encoding, char * string, size_t string_length, size_t * code_points_length_ptr)
{
  switch (encoding)
  {
    case CHARSET_UTF7:
      return unicode_read_string_utf7(string, string_length, code_points_length_ptr);
    case CHARSET_UTF8:
      return unicode_read_string_utf8(string, string_length, code_points_length_ptr);
    case CHARSET_UTF16:
      return unicode_read_string_utf16(string, string_length, code_points_length_ptr);
    case CHARSET_UTF16BE:
      return unicode_read_string_utf16be(string, string_length, code_points_length_ptr);
    case CHARSET_UTF16LE:
      return unicode_read_string_utf16le(string, string_length, code_points_length_ptr);
    case CHARSET_UTF32:
      return unicode_read_string_utf32(string, string_length, code_points_length_ptr);
    case CHARSET_UTF32BE:
      return unicode_read_string_utf32be(string, string_length, code_points_length_ptr);
    case CHARSET_UTF32LE:
      return unicode_read_string_utf32le(string, string_length, code_points_length_ptr);
      
    case CHARSET_UTF1:
    case CHARSET_UTF9:
    case CHARSET_UTF18:
    case CHARSET_UTF18BE:
    case CHARSET_UTF18LE:
      assert(0); /* NOT YET IMPLEMENTED */
      
    default:
      assert(0);
  }
}

char * unicode_write_string(Charset encoding, uint32_t * code_points, size_t code_points_length, size_t * string_length_ptr)
{
  switch (encoding)
  {
    case CHARSET_UTF7:
      return unicode_write_string_utf7(code_points, code_points_length, string_length_ptr);
    case CHARSET_UTF8:
      return unicode_write_string_utf8(code_points, code_points_length, string_length_ptr);
    case CHARSET_UTF16:
      return unicode_write_string_utf16(code_points, code_points_length, string_length_ptr);
    case CHARSET_UTF16BE:
      return unicode_write_string_utf16be(code_points, code_points_length, string_length_ptr);
    case CHARSET_UTF16LE:
      return unicode_write_string_utf16le(code_points, code_points_length, string_length_ptr);
    case CHARSET_UTF32:
      return unicode_write_string_utf32(code_points, code_points_length, string_length_ptr);
    case CHARSET_UTF32BE:
      return unicode_write_string_utf32be(code_points, code_points_length, string_length_ptr);
    case CHARSET_UTF32LE:
      return unicode_write_string_utf32le(code_points, code_points_length, string_length_ptr);
      
    case CHARSET_UTF1:
    case CHARSET_UTF9:
    case CHARSET_UTF18:
    case CHARSET_UTF18BE:
    case CHARSET_UTF18LE:
      assert(0); /* NOT YET IMPLEMENTED */
      
    default:
      assert(0);
  }
}








