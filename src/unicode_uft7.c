

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "strings.h"
#include "endianness.h"

#include "unicode.h"




unsigned int unicode_code_point_byte_requirement_utf7(uint32_t code_point)
{
  assert(0); /* NOT YET IMPLEMENTED */
}
bool unicode_is_well_formed_utf7(char * string, size_t string_length)
{
  assert(0); /* NOT YET IMPLEMENTED */
}

unsigned int unicode_string_length_utf7(char * string, size_t string_length)
{
  assert(0); /* NOT YET IMPLEMENTED */
}

int unicode_read_utf7(char * string, uint32_t * code_point)
{
  assert(0); /* NOT YET IMPLEMENTED */
}
int unicode_write_utf7(uint32_t code_point, char * string)
{
  assert(0); /* NOT YET IMPLEMENTED */
}

uint32_t * unicode_read_string_utf7(char * string, size_t string_length, size_t * code_points_length_ptr)
{
  assert(0); /* NOT YET IMPLEMENTED */
}
/* expects null terminlated code point list */
char * unicode_write_string_utf7(uint32_t * code_points, size_t code_points_length, size_t * string_length_ptr)
{
  assert(0); /* NOT YET IMPLEMENTED */
}

