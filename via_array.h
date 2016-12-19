#include <stdbool.h>
#include <stdint.h>


#ifndef VIAARRAY_H
#define VIAARRAY_H


 struct ViaArray_data {

	int x_ref;
	int y_ref;
	int diameter;
	int holesize;
	uint32_t key;
};

  
/**
 * key & definition string are stored
 */  
struct ViaArray_array {
  struct ViaArray_data  *array;	
  size_t used;
  size_t size;
};

void ViaArray_init(struct ViaArray_array * array_ptr, size_t initialSize);
void ViaArray_free(struct ViaArray_array * array_ptr);
void ViaArray_insert_key(struct ViaArray_array * array_ptr, uint32_t via_key);
//* Fill an array with vias from a single layer  
bool ViaArray_fill(struct ViaArray_array * array_ptr, FILE *f_src, int via_layer);

void ViaArray_report(struct ViaArray_array * array_ptr);
//* Sort an array by key, ie:group all like vias together
void ViaArray_sort(struct ViaArray_array * array_ptr);

#endif //*VIAARRAY_H
