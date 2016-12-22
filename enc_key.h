/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 */

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
