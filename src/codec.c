
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>

#include "charset.h"
#include "iso_8859.h"
#include "list.h"
#include "mtest.h"
#include "unicode.h"


#include "codec.h"


struct Codec
{
  Charset charset;

  bool (*is_well_formed_callback)(Charset, char *, size_t);
  bool (*is_representable_callback)(Charset, uint32_t *, size_t);

  int (*read_callback)(Charset, char *, uint32_t *);
  int (*write_callback)(Charset, uint32_t, char *);

  uint32_t * (*read_string_callback)(Charset, char *, size_t, size_t *);
  char * (*write_string_callback)(Charset, uint32_t *, size_t, size_t *);
};

static bool codec_unicode_is_representable_callback(
  Charset charset,
  uint32_t * code_points,
  size_t code_points_length
  )
{
  for (size_t k = 0; k < code_points_length; k++)
  {
    if (!unicode_is_valid_code_point(code_points[k]))
      return false;
  }

  return true;
}

static bool codec_ascii_is_well_formed(
  Charset charset,
  char * string,
  size_t string_length
  )
{
  for (size_t k = 0; k < string_length; k++)
  {
    if (string[k] & 0x80)
      return false;
  }

  return true;
}

static bool codec_ascii_is_representable(
  Charset charset,
  uint32_t * code_points,
  size_t code_points_length
  )
{
  for (size_t k = 0; k < code_points_length; k++)
  {
    if (code_points[k] >= 0x80)
      return false;
  }

  return true;
}

static int codec_ascii_read(
  Charset charset,
  char * string,
  uint32_t * code_point
  )
{
  if (*string & 0x80)
  {
    *code_point = *string;
    return 1;
  }
  else
    return 0;
}

static int codec_ascii_write(
  Charset charset,
  uint32_t code_point,
  char * string
  )
{
  if (code_point < 0x80)
  {
    *string = (char) code_point;
    return 1;
  }
  else
    return 0;
}

static uint32_t * codec_ascii_read_string(
  Charset charset,
  char * string,
  size_t string_length,
  size_t * code_points_length_ptr
  )
{
  assert(codec_ascii_is_well_formed(charset, string, string_length));

  uint32_t * ret = (uint32_t *) _malloc(sizeof(uint32_t) * string_length);

  for (size_t k = 0; k < string_length; k++)
  {
    ret[k] = (uint32_t) string[k];
  }
  *code_points_length_ptr = string_length;

  return ret;
}

static char * codec_ascii_write_string(
  Charset charset,
  uint32_t * code_points,
  size_t code_points_length,
  size_t * string_length_ptr
  )
{
  assert(codec_ascii_is_representable(
            charset,
            code_points,
            code_points_length
            ));

  char * ret = (char *) _malloc(sizeof(char) * code_points_length);
  assert(ret);

  for (size_t k = 0; k < code_points_length; k++)
  {
    ret[k] = (char) code_points[k];
  }
  *string_length_ptr = code_points_length;

  return ret;
}



static bool codec_set_callbacks(Codec * codec, Charset charset)
{
  switch (charset)
  {
    /* NOT SUPPORTED BY CODEC (yet) */
    case CHARSET_UTF1:
    case CHARSET_UTF9:
    case CHARSET_UTF18:
    case CHARSET_UTF18BE:
    case CHARSET_UTF18LE:
    case CHARSET_ISO_8859_12:
      return false;

    /* UNICODE */
    case CHARSET_UTF7:
    case CHARSET_UTF8:
    case CHARSET_UTF16:
    case CHARSET_UTF16BE:
    case CHARSET_UTF16LE:
    case CHARSET_UTF32:
    case CHARSET_UTF32BE:
    case CHARSET_UTF32LE:
      codec->is_well_formed_callback = unicode_is_well_formed;
      codec->is_representable_callback= codec_unicode_is_representable_callback;
      codec->read_callback = unicode_read;
      codec->write_callback = unicode_write;
      codec->read_string_callback = unicode_read_string;
      codec->write_string_callback = unicode_write_string;
      return true;

    /* ISO/IEC 8859 */
    case CHARSET_ISO_8859_1:
    case CHARSET_ISO_8859_2:
    case CHARSET_ISO_8859_3:
    case CHARSET_ISO_8859_4:
    case CHARSET_ISO_8859_5:
    case CHARSET_ISO_8859_6:
    case CHARSET_ISO_8859_7:
    case CHARSET_ISO_8859_8:
    case CHARSET_ISO_8859_9:
    case CHARSET_ISO_8859_10:
    case CHARSET_ISO_8859_11:
    case CHARSET_ISO_8859_13:
    case CHARSET_ISO_8859_14:
    case CHARSET_ISO_8859_15:
    case CHARSET_ISO_8859_16:
      codec->is_well_formed_callback = iso_8859_is_well_formed;
      codec->is_representable_callback = iso_8859_can_be_represented;
      codec->read_callback = iso_8859_read;
      codec->write_callback = iso_8859_write;
      codec->read_string_callback = iso_8859_read_string;
      codec->write_string_callback = iso_8859_write_string;
      return true;

    /* ASCII CHARSET IS BEST CHARSET */
    case CHARSET_ASCII:
      codec->is_well_formed_callback = codec_ascii_is_well_formed;
      codec->is_representable_callback = codec_ascii_is_representable;
      codec->read_callback = codec_ascii_read;
      codec->write_callback = codec_ascii_write;
      codec->read_string_callback = codec_ascii_read_string;
      codec->write_string_callback = codec_ascii_write_string;
      return true;

    /* NOT A VALID CHARSET */
    default:
      assert(0);
  }
}


List * codec_supported_charsets()
{
  List * list = list_new(LIST_TYPE_ARRAY_LIST);

  list_add(list, int_to_any(CHARSET_ASCII));
  list_add(list, int_to_any(CHARSET_UTF7));
  list_add(list, int_to_any(CHARSET_UTF8));
  list_add(list, int_to_any(CHARSET_UTF16));
  list_add(list, int_to_any(CHARSET_UTF16BE));
  list_add(list, int_to_any(CHARSET_UTF16LE));
  list_add(list, int_to_any(CHARSET_UTF32));
  list_add(list, int_to_any(CHARSET_UTF32BE));
  list_add(list, int_to_any(CHARSET_UTF32LE));
  list_add(list, int_to_any(CHARSET_ISO_8859_1));
  list_add(list, int_to_any(CHARSET_ISO_8859_2));
  list_add(list, int_to_any(CHARSET_ISO_8859_3));
  list_add(list, int_to_any(CHARSET_ISO_8859_4));
  list_add(list, int_to_any(CHARSET_ISO_8859_5));
  list_add(list, int_to_any(CHARSET_ISO_8859_6));
  list_add(list, int_to_any(CHARSET_ISO_8859_7));
  list_add(list, int_to_any(CHARSET_ISO_8859_8));
  list_add(list, int_to_any(CHARSET_ISO_8859_9));
  list_add(list, int_to_any(CHARSET_ISO_8859_10));
  list_add(list, int_to_any(CHARSET_ISO_8859_11));
  list_add(list, int_to_any(CHARSET_ISO_8859_13));
  list_add(list, int_to_any(CHARSET_ISO_8859_14));
  list_add(list, int_to_any(CHARSET_ISO_8859_15));
  list_add(list, int_to_any(CHARSET_ISO_8859_16));

  return list;
}


Codec * codec_new(Charset charset)
{
  Codec * ret;

  ret = (Codec *) _malloc(sizeof(Codec));
  assert(ret);

  ret->charset = charset;
  if (!codec_set_callbacks(ret, charset))
  {
    _free(ret);
    return NULL;
  }

  return ret;

}
void codec_destroy(Codec * codec)
{
  assert(codec);

  _free(codec);
}

Charset codec_get_charset(Codec * codec)
{
  assert(codec);

  return codec->charset;
}

bool codec_is_well_formed(
  Codec * codec,
  char * string,
  size_t string_length
  )
{
  assert(codec);

  return codec->is_well_formed_callback(codec->charset, string, string_length);
}
bool codec_is_representable(
  Codec * codec,
  uint32_t * code_points,
  size_t code_points_length
  )
{
  assert(codec);
  
  return codec->is_representable_callback(
      codec->charset,
      code_points,
      code_points_length
      );
}


int codec_read(Codec * codec, char * string, uint32_t * code_point)
{
  assert(codec);

  return codec->read_callback(codec->charset, string, code_point);
}

int codec_write(Codec * codec, uint32_t code_point, char * string)
{
  assert(codec);

  return codec->write_callback(codec->charset, code_point, string);
}

uint32_t * codec_read_string(
  Codec * codec,
  char * string,
  size_t string_length,
  size_t * code_points_length_ptr
  )
{
  assert(codec);

  return codec->read_string_callback(
    codec->charset,
    string,
    string_length,
    code_points_length_ptr
    );
}
char * codec_write_string(
  Codec * codec,
  uint32_t * code_points,
  size_t code_points_length,
  size_t * string_length_ptr
  )
{
  assert(codec);

  return codec->write_string_callback(
    codec->charset,
    code_points,
    code_points_length,
    string_length_ptr
    );
}
