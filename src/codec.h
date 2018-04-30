
#ifndef __CODEC_H
#define __CODEC_H

#include <stdbool.h>
#include <stdint.h>
#include <sys/types.h>

#include "charset.h"


struct Codec;
typedef struct Codec Codec;


List * codec_supported_charsets();


Codec * codec_new(Charset charset);
void codec_destroy(Codec * codec);

Charset codec_get_charset(Codec * codec);

bool codec_is_well_formed(
  Codec * codec,
  char * string,
  size_t string_length
  );
bool codec_is_representable(
  Codec * codec,
  uint32_t * code_points,
  size_t code_points_length
  );

int codec_read(Codec * codec, char * string, uint32_t * code_point);
int codec_write(Codec * codec, uint32_t code_point, char * string);

uint32_t * codec_read_string(
  Codec * codec,
  char * string,
  size_t string_length,
  size_t * code_points_length_ptr
  );
char * codec_write_string(
  Codec * codec,
  uint32_t * code_points,
  size_t code_points_length,
  size_t * string_length_ptr
  );




#endif


