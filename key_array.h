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

#include <stdbool.h>
#include <stdint.h>

#ifndef KEYARRAY_H
#define KEYARRAY_H

struct KeyArray_aperture {
	uint32_t key;
	char definition[32];
	char pour_def[32];
};

/**
 * key & definition string are stored
 */  
struct KeyArray_array {
  struct KeyArray_aperture *array;	
  size_t used;
  size_t size;
  int pour_clearance;
};

void KeyArray_init(struct KeyArray_array * array_ptr, size_t initialSize);
void KeyArray_insert_key(struct KeyArray_array * array_ptr, uint32_t element);
void KeyArray_free(struct KeyArray_array * array_ptr);
bool KeyArray_search_key(struct KeyArray_array * array_ptr, uint32_t element, int * idx_match);
bool KeyArray_insert_key_unique(struct KeyArray_array * array_ptr, uint32_t element);

#endif //*KEYARRAY_H
