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
#include "track_array.h"
#include "pcb.h"
#include "mystrings.h"


/**
 * TrackArray_init
 * initialise array to initialise size
 *  7-12-2016 requires code to test for allocation 
 * change type from void to bool
 */ 
void TrackArray_init( struct TrackArray_array * array_ptr, size_t initialSize) {
  array_ptr->array = (struct TrackArray_data *)malloc(initialSize * sizeof(struct TrackArray_data));
  array_ptr->used = 0;
  array_ptr->size = initialSize;
} //* END: init function


/**
 * TrackArray_free
 * free memory
 * 07-12-2016
 * check for NULL postruct TrackArray_data
 * check free is good
 * change type from void to bool
 */ 
void TrackArray_free( struct TrackArray_array * array_ptr) {
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
void TrackArray_insert_key( struct TrackArray_array * array_ptr, uint32_t track_key) {
  if (array_ptr->used == array_ptr->size) {
    array_ptr->size += 1;
    array_ptr->array = (struct TrackArray_data *)realloc(array_ptr->array, array_ptr->size * sizeof(struct TrackArray_data));
  } //* END: if
  array_ptr->array[array_ptr->used++].key = track_key;
} //* END: insert_key function


/**
 * TrackArray_fill
 * fill an array with track data
 */ 
bool TrackArray_fill(struct TrackArray_array * array_ptr, FILE *f_src, int track_layer) {
	

			char brd_data[64];
			int num_of_vars;
			int x1;
			int y1;
			int x2;
			int y2;
			int width;
			int layer;
			int user_routed;
			uint32_t key;
			int curr_index = 0;

			TrackArray_init(array_ptr, 1);

			while ( fgets(brd_data, 64, f_src) != NULL ) {
					
							
			if ( (strcmp(brd_data, COMP_TRACK) == 0 ) || (strcmp(brd_data, FREE_TRACK) == 0 ) ) {
				
				fgets(brd_data, 64, f_src);


				num_of_vars = sscanf(brd_data, "%5d%5d%5d%5d%4d%2d%1d", &x1, &y1, &x2, &y2, &width, &layer, &user_routed);
				if ( num_of_vars != PCB_NUM_TRK_VARS ) {
					fprintf(stderr, "Malformed line\n");
					return false;
				} //* END: if
				
				if ( layer == track_layer ) {
					key = ( ( width << 13) | ( width << 3 ) | PAD_SHAPE_CIRC);
					TrackArray_insert_key( array_ptr, key);
					curr_index = array_ptr->used - 1;
					array_ptr->array[curr_index].x1 = x1;
					array_ptr->array[curr_index].y1 = y1;
					array_ptr->array[curr_index].x2 = x2;
					array_ptr->array[curr_index].y2 = y2;
					array_ptr->array[curr_index].width = width;
					array_ptr->array[curr_index].layer = layer;
					array_ptr->array[curr_index].user_routed = user_routed;
					} //* END: if
			} //* END: if
			

	} //* END: while ( fgets(brd_data, 64, src) != NULL )
	rewind(f_src);					
	return true;			
} //* END: fill function				


/**
 * TrackArray_report
 * print array to stderr
 */ 
void TrackArray_report(struct TrackArray_array * array_ptr) {
	
		int index = 0;
		
	fprintf(stderr,"\n**** Track List ****\n");		
	
	for ( index=0; index < array_ptr->used; index++ ) {

		fprintf(stderr, "Track Apt Key: %d\n", array_ptr->array[index].key);
		fprintf(stderr, "X1: %d\tY1: %d\n", array_ptr->array[index].x1, array_ptr->array[index].y1);
		fprintf(stderr, "X2: %d\tY2: %d\n", array_ptr->array[index].x2, array_ptr->array[index].y2);
		fprintf(stderr, "Width: %d\n", array_ptr->array[index].width);
		fprintf(stderr, "Layer: %d\n", array_ptr->array[index].layer);
		fprintf(stderr, "User Routed: %d\n\n", array_ptr->array[index].user_routed);
	} //* END: for
} //* END: report function


/**
 *  TrackArray_sort sort tracks based on width
 * 
 *  Sort function based on exmaple in the book
 *  "The Art Of Programming Computer Science With C"
 *  By Steven C. Lawlor
 *  PWS Publishing Company
 */ 
 void TrackArray_sort(struct TrackArray_array * array_ptr) {
	
	struct TrackArray_data tmp_data;
	struct TrackArray_data *curr_data, *next_data, *swap_data;
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
				memcpy(swap_data, curr_data, sizeof (struct TrackArray_data));
				//*list[ position ]   = list[ position +1];
				memcpy(curr_data, next_data, sizeof (struct TrackArray_data));
				//*list[ position +1] = swap;
				memcpy(next_data, swap_data, sizeof (struct TrackArray_data));
				
				//* Indicate swap has been made
				swap_made = 1;

			} //* END: if
		--end_idx;	
	} //* END: while
} //* END: sort function
