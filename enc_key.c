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

#include "pcb.h"
#include "enc_key.h"

/**
 * EncodeKey_arc
 * 
 */
uint32_t EncodeKey_arc (struct Primitive_arc_data * ptr) {
	
	uint32_t key_value;

	key_value = ( (ptr->linewidth << 13) | (ptr->linewidth << 3) | PAD_SHAPE_CIRC );

return key_value;
} //* EncodeKey_arc

/**
 * EncodeKey_pad
 * 
 */
uint32_t EncodeKey_pad (struct Primitive_pad_data * ptr) {
	
	uint32_t key_value;

	key_value = ( (ptr->x_size << 13) | (ptr->y_size << 3) | ptr->shape);

return key_value;
} //* EncodeKey_pad

/**
 * EncodeKey_string
 * 
 */
uint32_t EncodeKey_string (struct Primitive_string_data * ptr) {
	
	uint32_t key_value;

	key_value = ( (ptr->linewidth << 13) | (ptr->linewidth << 3) | PAD_SHAPE_CIRC);

return key_value;
} //* EncodeKey_string

/**
 * EncodeKey_track
 * 
 */
uint32_t EncodeKey_track (struct Primitive_track_data * ptr) {
	
	uint32_t key_value;

	key_value = ( (ptr->width << 13) | (ptr->width << 3) | PAD_SHAPE_CIRC );

return key_value;
} //* EncodeKey_track

/**
 * EncodeKey_via
 * 
 */
uint32_t EncodeKey_via (struct Primitive_via_data * ptr) {
	
	uint32_t key_value;

	key_value = ( (ptr->diameter << 13) | (ptr->diameter << 3) | PAD_SHAPE_CIRC );

return key_value;
} //* EncodeKey_via

uint32_t EncodeKey_drill_guide (int diameter) {
	
	uint32_t key_value;

	key_value = ( (diameter << 13) | (diameter << 3) | PAD_SHAPE_DGD );

return key_value;
} //* EncodeKey_via
