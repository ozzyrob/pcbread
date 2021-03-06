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


#ifndef ARCARRAY_H
#define ARCARRAY_H


 struct ArcArray_data {
 	int x_ref;
	int y_ref;
	int radius;
	int segments;
	int width;
	int layer;
	uint32_t key;

};

  
/**
 * key & definition string are stored
 */  
struct ArcArray_array {
  struct ArcArray_data  *array;	
  size_t used;
  size_t size;
};

void ArcArray_init(struct ArcArray_array * array_ptr, size_t initialSize);
void ArcArray_free(struct ArcArray_array * array_ptr);
void ArcArray_insert_key(struct ArcArray_array * array_ptr, uint32_t arc_key);
//* Fill an array with arcs from a single layer  
bool ArcArray_fill(struct ArcArray_array * array_ptr, FILE *f_src, int arc_layer);

void ArcArray_report(struct ArcArray_array * array_ptr);
//* Sort an array by key, ie:group all like arcs together
void ArcArray_sort(struct ArcArray_array * array_ptr);

#endif //*ARCARRAY_H
