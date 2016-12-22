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


#ifndef VIAARRAY_H
#define VIAARRAY_H


 struct ViaArray_data {

	int x_ref;
	int y_ref;
	int diameter;
	int holesize;
	uint32_t key;
};

  
/**
 * key & definition string are stored
 */  
struct ViaArray_array {
  struct ViaArray_data  *array;	
  size_t used;
  size_t size;
};

void ViaArray_init(struct ViaArray_array * array_ptr, size_t initialSize);
void ViaArray_free(struct ViaArray_array * array_ptr);
void ViaArray_insert_key(struct ViaArray_array * array_ptr, uint32_t via_key);
//* Fill an array with vias from a single layer  
bool ViaArray_fill(struct ViaArray_array * array_ptr, FILE *f_src, int via_layer);

void ViaArray_report(struct ViaArray_array * array_ptr);
//* Sort an array by key, ie:group all like vias together
void ViaArray_sort(struct ViaArray_array * array_ptr);

#endif //*VIAARRAY_H
