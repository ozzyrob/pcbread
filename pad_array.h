#include <stdbool.h>
#include <stdint.h>


#ifndef PADARRAY_H
#define PADARRAY_H


 struct PadArray_data {
 	int x_ref;
	int y_ref;
	uint32_t key;
	int hole_size;
	int pwr_gnd;
	int layer;
	char pad_name[6];
};

  
/**
 * key & definition string are stored
 */  
struct PadArray_array {
  struct PadArray_data  *array;	
  size_t used;
  size_t size;
};

void PadArray_init(struct PadArray_array * array_ptr, size_t initialSize);
void PadArray_free(struct PadArray_array * array_ptr);
void PadArray_insert_key(struct PadArray_array * array_ptr, uint32_t pad_key);
//* Fill an array with pads from a single layer  
bool PadArray_fill(struct PadArray_array * array_ptr, FILE *f_src, int pad_layer);

void PadArray_report(struct PadArray_array * array_ptr);
//* Sort an array by key, ie:group all like pads together
void PadArray_sort(struct PadArray_array * array_ptr);

#endif //*PADARRAY_H
