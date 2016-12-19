#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "str_array.h"
#include "pcb.h"
#include "mystrings.h"

/**
 * StrArray_init
 * initialise array to initialise size
 *  7-12-2016 requires code to test for allocation 
 * change type from void to bool
 */ 
void StrArray_init( struct StrArray_array * array_ptr, size_t initialSize) {
  array_ptr->array = (struct StrArray_data *)malloc(initialSize * sizeof(struct StrArray_data));
  array_ptr->used = 0;
  array_ptr->size = initialSize;
}

/**
 * StrArray_free
 * free memory
 * 07-12-2016
 * check for NULL postruct StrArray_data
 * check free is good
 * change type from void to bool
 */ 
void StrArray_free( struct StrArray_array * array_ptr) {
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
void StrArray_insert_key( struct StrArray_array * array_ptr, uint32_t str_key) {
  if (array_ptr->used == array_ptr->size) {
    array_ptr->size += 1;
    array_ptr->array = (struct StrArray_data *)realloc(array_ptr->array, array_ptr->size * sizeof(struct StrArray_data));
  }
  array_ptr->array[array_ptr->used++].key = str_key;
  //* fprintf(stderr,"Size: %d\tUsed: %d\n", array_ptr->size, array_ptr->used);
}
bool StrArray_fill(struct StrArray_array * array_ptr, FILE *f_src, int str_layer) {
	

			char brd_data[64];
			int num_of_vars;
			int x_ref;
			int y_ref;
			int height;
			int rotation;
			int width;
			int layer;
			uint32_t key;
			int curr_index = 0;

			StrArray_init(array_ptr, 1);

			while ( fgets(brd_data, 64, f_src) != NULL ) {
							
			if ( (strcmp(brd_data, COMP_STRING) == 0 ) || (strcmp(brd_data, FREE_STRING) == 0 ) ) {
				
				fgets(brd_data, 64, f_src);
			    //* fprintf(stderr, "Str Data %s", brd_data);
			    
				num_of_vars = sscanf(brd_data, "%5d%5d%4d%2d%3d%2d", &x_ref, &y_ref, &height, &rotation, &width, &layer);
				if ( num_of_vars != PCB_NUM_STR_VARS ) {
					fprintf(stderr, "Malformed line\n");
					return false;
				}
				
				if ( layer == str_layer ) {
					key = ( ( width << 13) | ( width << 3 ) | PAD_SHAPE_CIRC);
					StrArray_insert_key( array_ptr, key);
					curr_index = array_ptr->used-1;
					array_ptr->array[curr_index].x_ref = x_ref;
					array_ptr->array[curr_index].y_ref = y_ref;
					array_ptr->array[curr_index].height = height;
					array_ptr->array[curr_index].rotation = rotation;
					array_ptr->array[curr_index].width = width;
					array_ptr->array[curr_index].layer = layer;
					fgets(array_ptr->array[curr_index].str_text, 33, f_src);
					}
			}
			

	} //* END: while ( fgets(brd_data, 64, src) != NULL )
	rewind(f_src);				
	return true;			
}				

void StrArray_report(struct StrArray_array * array_ptr) {
	
		int index = 0;
		
	fprintf(stderr,"\n**** Str List ****\n");	

	for ( index=0; index < array_ptr->used; index++ ) {

		fprintf(stderr, "Str Apt Key: %d\n", array_ptr->array[index].key);
		fprintf(stderr, "Xref: %d\tYref: %d\n", array_ptr->array[index].x_ref, array_ptr->array[index].y_ref);
		fprintf(stderr, "Height: %d\n", array_ptr->array[index].height);
		fprintf(stderr, "Width: %d\n",  array_ptr->array[index].width);
		fprintf(stderr, "Layer: %d\n", array_ptr->array[index].layer);
		fprintf(stderr, "String Text: %s\n", array_ptr->array[index].str_text);

	}
}

/**
 *  Sort function based on exmaple in the book 
 *  "The Art Of Programming Computer Science With C"
 *  By Steven C. Lawlor
 *  PWS Publishing Company
 */ 
 
 void StrArray_sort(struct StrArray_array * array_ptr) {
	
	struct StrArray_data tmp_data;
	struct StrArray_data *curr_data, *next_data, *swap_data;
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
				memcpy(swap_data, curr_data, sizeof (struct StrArray_data));
		
				//*list[ position ]   = list[ position +1];
				memcpy(curr_data, next_data, sizeof (struct StrArray_data));
		
				//*list[ position +1] = swap;
				memcpy(next_data, swap_data, sizeof (struct StrArray_data));
				swap_made = 1;

			} //* END: if
		--end_idx;	
	} //* END: while
} //* END: sort function
