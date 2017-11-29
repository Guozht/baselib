
#ifndef __BASELIB_ENDIANNESS_H
#define __BASELIB_ENDIANNESS_H


enum Endianness
{
  ENDIANNESS_NONE = 0x0,
  ENDIANNESS_BIG = 0x01,
  ENDIANNESS_LITTLE = 0x80
};
typedef enum Endianness Endianness;

Endianness endianness_flip(Endianness e);

#endif
