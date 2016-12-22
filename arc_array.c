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
#include "arc_array.h"
#include "pcb.h"
#include "mystrings.h"

/**
 * ArcArray_init
 * initialise array to initialise size
 *  7-12-2016 requires code to test for allocation 
 * change type from void to bool
 */ 
void ArcArray_init( struct ArcArray_array * array_ptr, size_t initialSize) {
  array_ptr->array = (struct ArcArray_data *)malloc(initialSize * sizeof(struct ArcArray_data));
  array_ptr->used = 0;
  array_ptr->size = initialSize;
}

/**
 * ArcArray_free
 * free memory
 * 07-12-2016
 * check for NULL postruct ArcArray_data
 * check free is good
 * change type from void to bool
 */ 
void ArcArray_free( struct ArcArray_array * array_ptr) {
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
void ArcArray_insert_key( struct ArcArray_array * array_ptr, uint32_t arc_key) {
  if (array_ptr->used == array_ptr->size) {
    array_ptr->size += 1;
    array_ptr->array = (struct ArcArray_data *)realloc(array_ptr->array, array_ptr->size * sizeof(struct ArcArray_data));
  }
  array_ptr->array[array_ptr->used++].key = arc_key;
  //* fprintf(stderr,"Size: %d\tUsed: %d\n", array_ptr->size, array_ptr->used);
}
bool ArcArray_fill(struct ArcArray_array * array_ptr, FILE *f_src, int arc_layer) {
	

			char brd_data[64];
			int x_ref;
			int y_ref;
			int radius;
			int segments;
			int width;
			int layer;
			uint32_t key;
			int curr_index = 0;
			int num_of_vars = 0;

			ArcArray_init(array_ptr, 1);

			while ( fgets(brd_data, 64, f_src) != NULL ) {
							
			if ( (strcmp(brd_data, COMP_ARC) == 0 ) || (strcmp(brd_data, FREE_ARC) == 0 ) ) {
				
				fgets(brd_data, 64, f_src);
			    //* fprintf(stderr, "Arc Data %s", brd_data);
			    
				num_of_vars = sscanf(brd_data, "%5d%5d%5d%3d%3d%2d", &x_ref, &y_ref, &radius, &segments, &width, &layer);
				if ( num_of_vars != PCB_NUM_ARC_VARS ) {
					fprintf(stderr, "Malformed line\n");
					return false;
				}
				
				if ( layer == arc_layer ) {
					key = ( ( width << 13) | ( width << 3 ) | PAD_SHAPE_CIRC);
					ArcArray_insert_key( array_ptr, key);
					curr_index = array_ptr->used-1;
					array_ptr->array[curr_index].x_ref = x_ref;
					array_ptr->array[curr_index].y_ref = y_ref;
					array_ptr->array[curr_index].radius = radius;
					array_ptr->array[curr_index].segments = segments;
					array_ptr->array[curr_index].layer = layer;
					array_ptr->array[curr_index].width = width;
					}
			}
			

	} //* END: while ( fgets(brd_data, 64, src) != NULL )
	rewind(f_src);				
	return true;			
}				

void ArcArray_report(struct ArcArray_array * array_ptr) {
	
		int index = 0;
		
	fprintf(stderr,"\n**** Arc List ****\n");	

	for ( index=0; index < array_ptr->used; index++ ) {

		fprintf(stderr, "Arc Apt Key: %d\n", array_ptr->array[index].key);
		fprintf(stderr, "Xref: %d\tYref: %d\n", array_ptr->array[index].x_ref, array_ptr->array[index].y_ref);
		fprintf(stderr, "Radius %d\n", array_ptr->array[index].radius);
		fprintf(stderr, "Segments: %d\n", array_ptr->array[index].segments);
		fprintf(stderr, "Linewidth: %d\n",  array_ptr->array[index].width);
		fprintf(stderr, "Layer: %d\n", array_ptr->array[index].layer);


	}
}

/**
 *  Sort function based on exmaple in the book 
 *  "The Art Of Programming Computer Science With C"
 *  By Steven C. Lawlor
 *  PWS Publishing Company
 */ 
 
 void ArcArray_sort(struct ArcArray_array * array_ptr) {
	
	struct ArcArray_data tmp_data;
	struct ArcArray_data *curr_data, *next_data, *swap_data;
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
				memcpy(swap_data, curr_data, sizeof (struct ArcArray_data));
		
				//*list[ position ]   = list[ position +1];
				memcpy(curr_data, next_data, sizeof (struct ArcArray_data));
		
				//*list[ position +1] = swap;
				memcpy(next_data, swap_data, sizeof (struct ArcArray_data));
				swap_made = 1;

			} //* END: if
		--end_idx;	
	} //* END: while
} //* END: sort function
