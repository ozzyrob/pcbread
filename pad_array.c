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
#include "pad_array.h"
#include "pcb.h"
#include "mystrings.h"

/**
 * PadArray_init
 * initialise array to initialise size
 *  7-12-2016 requires code to test for allocation 
 * change type from void to bool
 */ 
void PadArray_init( struct PadArray_array * array_ptr, size_t initialSize) {
  array_ptr->array = (struct PadArray_data *)malloc(initialSize * sizeof(struct PadArray_data));
  array_ptr->used = 0;
  array_ptr->size = initialSize;
}

/**
 * PadArray_free
 * free memory
 * 07-12-2016
 * check for NULL postruct PadArray_data
 * check free is good
 * change type from void to bool
 */ 
void PadArray_free( struct PadArray_array * array_ptr) {
  free(array_ptr->array);
  array_ptr->array = NULL;
  array_ptr->used = array_ptr->size = 0;
}


	/**
 * KeyArray_insert
 * insert key, resize if required
 * 7-12-2016 requires code to test for allocation 
 * change type from void to bool
 */ 
void PadArray_insert_key( struct PadArray_array * array_ptr, uint32_t pad_key) {
  if (array_ptr->used == array_ptr->size) {
    array_ptr->size += 1;
    array_ptr->array = (struct PadArray_data *)realloc(array_ptr->array, array_ptr->size * sizeof(struct PadArray_data));
  }
  array_ptr->array[array_ptr->used++].key = pad_key;
  //* fprintf(stderr,"Size: %d\tUsed: %d\n", array_ptr->size, array_ptr->used);
}
bool PadArray_fill(struct PadArray_array * array_ptr, FILE *f_src, int pad_layer) {
	

			char brd_data[64];
			int num_of_vars;
			int x_ref, y_ref;
			int x_size, y_size;
			int shape;
			int hole_size;
			int pwr_gnd;
			int layer;
			uint32_t key;
			int curr_index = 0;

			PadArray_init(array_ptr, 1);

			while ( fgets(brd_data, 64, f_src) != NULL ) {
							
			if ( (strcmp(brd_data, COMP_PAD) == 0 ) || (strcmp(brd_data, FREE_PAD) == 0 ) ) {
				
				fgets(brd_data, 64, f_src);
			    //* fprintf(stderr, "Pad Data %s", brd_data);
			    
				num_of_vars = sscanf(brd_data, "%5d%5d%4d%4d%1d%4d%1d%2d", &x_ref, &y_ref, &x_size, &y_size, &shape, &hole_size, &pwr_gnd, &layer);
				if ( num_of_vars != PCB_NUM_PAD_VARS ) {
					fprintf(stderr, "Malformed line\n");
					return false;
				}
				
				if ( layer == pad_layer ) {
					key = ( ( x_size << 13) | ( y_size << 3 ) | shape);
					PadArray_insert_key( array_ptr, key);
					curr_index = array_ptr->used-1;
					array_ptr->array[curr_index].x_ref = x_ref;
					array_ptr->array[curr_index].y_ref = y_ref;
					array_ptr->array[curr_index].hole_size = hole_size;
					array_ptr->array[curr_index].pwr_gnd = pwr_gnd;
					array_ptr->array[curr_index].layer = layer;
					fgets(array_ptr->array[curr_index].pad_name, 6, f_src);
					}
			}
			

	} //* END: while ( fgets(brd_data, 64, src) != NULL )
	rewind(f_src);				
	return true;			
}				

void PadArray_report(struct PadArray_array * array_ptr) {
	
		int index = 0;
		
	fprintf(stderr,"\n**** Pad List ****\n");	

	for ( index=0; index < array_ptr->used; index++ ) {

		fprintf(stderr, "Pad Apt Key: %d\n", array_ptr->array[index].key);
		fprintf(stderr, "Xref: %d\tYref: %d\n", array_ptr->array[index].x_ref, array_ptr->array[index].y_ref);
		fprintf(stderr, "Hole size %d\n", array_ptr->array[index].hole_size);
		fprintf(stderr, "Power - Ground: %d\n",  array_ptr->array[index].pwr_gnd);
		fprintf(stderr, "Layer: %d\n", array_ptr->array[index].layer);
		fprintf(stderr, "Pad Name: %s\n", array_ptr->array[index].pad_name);

	}
}

/**
 *  Sort function based on exmaple in the book 
 *  "The Art Of Programming Computer Science With C"
 *  By Steven C. Lawlor
 *  PWS Publishing Company
 */ 
 
 void PadArray_sort(struct PadArray_array * array_ptr) {
	
	struct PadArray_data tmp_data;
	struct PadArray_data *curr_data, *next_data, *swap_data;
	int position;
	int end_idx = array_ptr->used -1 ;
	int swap_made = 1;

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
				memcpy(swap_data, curr_data, sizeof (struct PadArray_data));
		
				//*list[ position ]   = list[ position +1];
				memcpy(curr_data, next_data, sizeof (struct PadArray_data));
		
				//*list[ position +1] = swap;
				memcpy(next_data, swap_data, sizeof (struct PadArray_data));
				swap_made = 1;

			} //* END: if
		--end_idx;	
	} //* END: while
} //* END: sort function
