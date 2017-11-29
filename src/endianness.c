
#include "endianness.h"

Endianness endianness_flip(Endianness e)
{
  switch (e)
  {
    case ENDIANNESS_BIG:
      return ENDIANNESS_LITTLE;
    case ENDIANNESS_LITTLE:
      return ENDIANNESS_BIG;
    default:
      return ENDIANNESS_NONE;
  }
}
