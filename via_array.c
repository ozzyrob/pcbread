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
#include <string.h>
#include "via_array.h"
#include "pcb.h"
#include "mystrings.h"


/**
 * ViaArray_init
 * initialise array to initialise size
 *  7-12-2016 requires code to test for allocation 
 * change type from void to bool
 */ 
void ViaArray_init( struct ViaArray_array * array_ptr, size_t initialSize) {
  array_ptr->array = (struct ViaArray_data *)malloc(initialSize * sizeof(struct ViaArray_data));
  array_ptr->used = 0;
  array_ptr->size = initialSize;
} //* END: init function


/**
 * ViaArray_free
 * free memory
 * 07-12-2016
 * check for NULL postruct ViaArray_data
 * check free is good
 * change type from void to bool
 */ 
void ViaArray_free( struct ViaArray_array * array_ptr) {
  free(array_ptr->array);
  array_ptr->array = NULL;
  array_ptr->used = array_ptr->size = 0;
} //* END: free function


/**
 * KeyArray_insert
 * insert key, resize if required
 * 7-12-2016 requires code to test for allocation 
 * change type from void to bool
 */ 
void ViaArray_insert_key( struct ViaArray_array * array_ptr, uint32_t via_key) {
  if (array_ptr->used == array_ptr->size) {
    array_ptr->size += 1;
    array_ptr->array = (struct ViaArray_data *)realloc(array_ptr->array, array_ptr->size * sizeof(struct ViaArray_data));
  } //* END: if
  array_ptr->array[array_ptr->used++].key = via_key;
} //* END: insert_key function


/**
 * ViaArray_fill
 * fill an array with via data
 */ 
bool ViaArray_fill(struct ViaArray_array * array_ptr, FILE *f_src, int via_layer) {
	

			char brd_data[64];
			int num_of_vars;
			int x_ref;
			int y_ref;
			int diameter;
			int holesize;
			uint32_t key;
			int curr_index = 0;

			ViaArray_init(array_ptr, 1);

			while ( fgets(brd_data, 64, f_src) != NULL ) {
					
							
			if ( (strcmp(brd_data, COMP_VIA) == 0 ) || (strcmp(brd_data, FREE_VIA) == 0 ) ) {
				
				fgets(brd_data, 64, f_src);


				num_of_vars = sscanf(brd_data, "%5d%5d%4d%4d", &x_ref, &y_ref, &diameter, &holesize);
				if ( num_of_vars != PCB_NUM_VIA_VARS ) {
					fprintf(stderr, "Malformed line\n");
					return false;
				} //* END: if
				
					key = ( ( diameter << 13) | ( diameter << 3 ) | PAD_SHAPE_CIRC);
					ViaArray_insert_key( array_ptr, key);
					curr_index = array_ptr->used - 1;
					array_ptr->array[curr_index].x_ref = x_ref;
					array_ptr->array[curr_index].y_ref = y_ref;
					array_ptr->array[curr_index].diameter = diameter;
					array_ptr->array[curr_index].holesize = holesize;

			} //* END: if
			

	} //* END: while ( fgets(brd_data, 64, src) != NULL )
	rewind(f_src);					
	return true;			
} //* END: fill function				


/**
 * ViaArray_report
 * print array to stderr
 */ 
void ViaArray_report(struct ViaArray_array * array_ptr) {
	
		int index = 0;
		
	fprintf(stderr,"\n**** Via List ****\n");		
	
	for ( index=0; index < array_ptr->used; index++ ) {

		fprintf(stderr, "X1: %d\tY1: %d\n", array_ptr->array[index].x_ref, array_ptr->array[index].y_ref);
		fprintf(stderr, "Diameter: %d\n", array_ptr->array[index].diameter);
		fprintf(stderr, "Holesize: %d\n", array_ptr->array[index].holesize);
	} //* END: for
} //* END: report function


/**
 *  ViaArray_sort sort vias based on width
 * 
 *  Sort function based on exmaple in the book
 *  "The Art Of Programming Computer Science With C"
 *  By Steven C. Lawlor
 *  PWS Publishing Company
 */ 
 void ViaArray_sort(struct ViaArray_array * array_ptr) {
	
	struct ViaArray_data tmp_data;
	struct ViaArray_data *curr_data, *next_data, *swap_data;
	int position;
	int end_idx = array_ptr->used -1 ;
	int swap_made = 1;

	//* If no swaps are made after an iteration from top to bottom
	//* we can exit
	 while ( end_idx > 0 && swap_made )
  {
		swap_made = 0;
		for (position = 0 ; position < end_idx ; ++position)
		
		if (array_ptr->array[ position ].key > array_ptr->array[ position +1].key)
			{
				/* Swapping */
				curr_data = &array_ptr->array[ position ];
				next_data = &array_ptr->array[ position +1];
				swap_data = &tmp_data;

				//* swap = array[ position ];
				memcpy(swap_data, curr_data, sizeof (struct ViaArray_data));
				//*list[ position ]   = list[ position +1];
				memcpy(curr_data, next_data, sizeof (struct ViaArray_data));
				//*list[ position +1] = swap;
				memcpy(next_data, swap_data, sizeof (struct ViaArray_data));
				
				//* Indicate swap has been made
				swap_made = 1;

			} //* END: if
		--end_idx;	
	} //* END: while
} //* END: sort function
