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

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "key_array.h"


/**
 * KeyArray_init
 * initialise array to initialise size
 *  7-12-2016 requires code to test for allocation 
 * change type from void to bool
 */ 
void KeyArray_init( struct KeyArray_array * array_ptr, size_t initialSize) {
  array_ptr->array = (struct KeyArray_aperture *)malloc(initialSize * sizeof(struct KeyArray_aperture));
  array_ptr->used = 0;
  array_ptr->size = initialSize;

}
/**
 * KeyArray_insert
 * insert key, resize if required
 * 7-12-2016 requires code to test for allocation 
 * change type from void to bool
 */ 
void KeyArray_insert_key( struct KeyArray_array * array_ptr, uint32_t element) {
  if (array_ptr->used == array_ptr->size) {
    array_ptr->size += 1;
    array_ptr->array = (struct KeyArray_aperture *)realloc(array_ptr->array, array_ptr->size * sizeof(struct KeyArray_aperture));
  }
  array_ptr->array[array_ptr->used++].key = element;
}

/**
 * KeyArray_search
 * search array for element
 * return true if found
 * idx_match = index where found
 * return false if no match
 * idx_match = 0
 */ 
bool KeyArray_search_key( struct KeyArray_array * array_ptr, uint32_t element, int * idx_match) {
	
	bool ret_val;
	int idx_curr;
	
	if ( array_ptr->used == 0 ) {
		ret_val = false;
		*idx_match = 0;
	}

	else {
		for ( idx_curr = 0; idx_curr < array_ptr->used; idx_curr++ ) {
			if ( element == array_ptr->array[idx_curr].key ) {
				ret_val = true;
				*idx_match = idx_curr;
				break;
			}
			else {
				ret_val = false;
				*idx_match = 0;
			}
		}	 
		
	}
	
	return ret_val;
}
/**
 * KeyArray_free
 * free memory
 * 07-12-2016
 * check for NULL postruct KeyArray_apertureer
 * check free is good
 * change type from void to bool
 */ 
void KeyArray_free( struct KeyArray_array * array_ptr) {
  free(array_ptr->array);
  array_ptr->array = NULL;
  array_ptr->used = array_ptr->size = 0;
}
/**
 * KeyArray_insert_unique
 * Insert element if not already in array
 */ 
bool KeyArray_insert_key_unique(struct KeyArray_array * array_ptr, uint32_t element) {
	
	int found_idx = 0;
	bool retn_val;
	
	if ( !KeyArray_search_key( array_ptr, element, &found_idx)) {
		KeyArray_insert_key(array_ptr, element);
		retn_val = true;
	} 
	else {
		retn_val = false;
	}

	return retn_val;
}
