#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "primitive.h"

#ifndef ENCODEKEYS_H
#define ENCODEKEYS_H

uint32_t EncodeKey_arc (struct Primitive_arc_data * ptr);
uint32_t EncodeKey_pad (struct Primitive_pad_data * ptr);
uint32_t EncodeKey_string (struct Primitive_string_data * ptr);
uint32_t EncodeKey_track (struct Primitive_track_data * ptr);
uint32_t EncodeKey_via (struct Primitive_via_data * ptr);
uint32_t EncodeKey_drill_guide (int diameter);

#endif /* ENCODEHEYS_H */
