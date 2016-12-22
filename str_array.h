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


#ifndef STRARRAY_H
#define STRARRAY_H


 struct StrArray_data {
 	int x_ref;
	int y_ref;
	int height;
	int rotation;
	int width;
	int layer;
	char str_text[33];
	uint32_t key;
};

  
/**
 * key & definition string are stored
 */  
struct StrArray_array {
  struct StrArray_data  *array;	
  size_t used;
  size_t size;
};

void StrArray_init(struct StrArray_array * array_ptr, size_t initialSize);
void StrArray_free(struct StrArray_array * array_ptr);
void StrArray_insert_key(struct StrArray_array * array_ptr, uint32_t str_key);
//* Fill an array with strs from a single layer  
bool StrArray_fill(struct StrArray_array * array_ptr, FILE *f_src, int str_layer);

void StrArray_report(struct StrArray_array * array_ptr);
//* Sort an array by key, ie:group all like strs together
void StrArray_sort(struct StrArray_array * array_ptr);

#endif //*STRARRAY_H
