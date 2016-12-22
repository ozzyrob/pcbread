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


#ifndef TRACKARRAY_H
#define TRACKARRAY_H


 struct TrackArray_data {

	int x1;
	int y1;
	int x2;
	int y2;
	int width;
	int layer;
	int user_routed;
	uint32_t key;
};

  
/**
 * key & definition string are stored
 */  
struct TrackArray_array {
  struct TrackArray_data  *array;	
  size_t used;
  size_t size;
};

void TrackArray_init(struct TrackArray_array * array_ptr, size_t initialSize);
void TrackArray_free(struct TrackArray_array * array_ptr);
void TrackArray_insert_key(struct TrackArray_array * array_ptr, uint32_t track_key);
//* Fill an array with tracks from a single layer  
bool TrackArray_fill(struct TrackArray_array * array_ptr, FILE *f_src, int track_layer);

void TrackArray_report(struct TrackArray_array * array_ptr);
//* Sort an array by key, ie:group all like tracks together
void TrackArray_sort(struct TrackArray_array * array_ptr);

#endif //*TRACKARRAY_H
