#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "fill_array.h"
#include "pcb.h"
#include "mystrings.h"


/**
 * FillArray_init
 * initialise array to initialise size
 *  7-12-2016 requires code to test for allocation 
 * change type from void to bool
 */ 
void FillArray_init( struct FillArray_array * array_ptr, size_t initialSize) {
  array_ptr->array = (struct FillArray_data *)malloc(initialSize * sizeof(struct FillArray_data));
  array_ptr->used = 0;
  array_ptr->size = initialSize;
} //* END: init function


/**
 * FillArray_free
 * free memory
 * 07-12-2016
 * check for NULL postruct FillArray_data
 * check free is good
 * change type from void to bool
 */ 
void FillArray_free( struct FillArray_array * array_ptr) {
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
void FillArray_insert_key( struct FillArray_array * array_ptr, uint32_t fill_key) {
  if (array_ptr->used == array_ptr->size) {
    array_ptr->size += 1;
    array_ptr->array = (struct FillArray_data *)realloc(array_ptr->array, array_ptr->size * sizeof(struct FillArray_data));
  } //* END: if
  array_ptr->array[array_ptr->used++].key = fill_key;
} //* END: insert_key function


/**
 * FillArray_fill
 * fill an array with fill data
 */ 
bool FillArray_fill(struct FillArray_array * array_ptr, FILE *f_src, int fill_layer) {
	

			char brd_data[64];
			int num_of_vars;
			int x1;
			int y1;
			int x2;
			int y2;
			int layer;
			uint32_t key;
			int curr_index = 0;

			FillArray_init(array_ptr, 1);

			while ( fgets(brd_data, 64, f_src) != NULL ) {
					
							
			if ( (strcmp(brd_data, COMP_FILL) == 0 ) || (strcmp(brd_data, FREE_FILL) == 0 ) ) {
				
				fgets(brd_data, 64, f_src);


				num_of_vars = sscanf(brd_data, "%5d%5d%5d%5d%2d", &x1, &y1, &x2, &y2, &layer);
				if ( num_of_vars != PCB_NUM_FILL_VARS ) {
					fprintf(stderr, "Malformed line\n");
					return false;
				} //* END: if
				
				if ( layer == fill_layer ) {
					key = PCB_FILL_KEY;
					FillArray_insert_key( array_ptr, key);
					curr_index = array_ptr->used - 1;
					array_ptr->array[curr_index].x1 = x1;
					array_ptr->array[curr_index].y1 = y1;
					array_ptr->array[curr_index].x2 = x2;
					array_ptr->array[curr_index].y2 = y2;
					array_ptr->array[curr_index].layer = layer;
					} //* END: if
			} //* END: if
			

	} //* END: while ( fgets(brd_data, 64, src) != NULL )
	rewind(f_src);					
	return true;			
} //* END: fill function				


/**
 * FillArray_report
 * print array to stderr
 */ 
void FillArray_report(struct FillArray_array * array_ptr) {
	
		int index = 0;
		
	fprintf(stderr,"\n**** Fill List ****\n");		
	
	for ( index=0; index < array_ptr->used; index++ ) {

		fprintf(stderr, "Fill Apt Key: %d\n", array_ptr->array[index].key);
		fprintf(stderr, "X1: %d\tY1: %d\n", array_ptr->array[index].x1, array_ptr->array[index].y1);
		fprintf(stderr, "X2: %d\tY2: %d\n", array_ptr->array[index].x2, array_ptr->array[index].y2);
		fprintf(stderr, "Layer: %d\n", array_ptr->array[index].layer);
	} //* END: for
} //* END: report function


/**
 *  FillArray_sort sort fills based on width
 * 
 *  Sort function based on exmaple in the book
 *  "The Art Of Programming Computer Science With C"
 *  By Steven C. Lawlor
 *  PWS Publishing Company
 */ 
 void FillArray_sort(struct FillArray_array * array_ptr) {
	
	struct FillArray_data tmp_data;
	struct FillArray_data *curr_data, *next_data, *swap_data;
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
				memcpy(swap_data, curr_data, sizeof (struct FillArray_data));
				//*list[ position ]   = list[ position +1];
				memcpy(curr_data, next_data, sizeof (struct FillArray_data));
				//*list[ position +1] = swap;
				memcpy(next_data, swap_data, sizeof (struct FillArray_data));
				
				//* Indicate swap has been made
				swap_made = 1;

			} //* END: if
		--end_idx;	
	} //* END: while
} //* END: sort function
