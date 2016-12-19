#include <stdbool.h>
#include <stdint.h>


#ifndef FILLARRAY_H
#define FILLARRAY_H


 struct FillArray_data {

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
struct FillArray_array {
  struct FillArray_data  *array;	
  size_t used;
  size_t size;
};

void FillArray_init(struct FillArray_array * array_ptr, size_t initialSize);
void FillArray_free(struct FillArray_array * array_ptr);
void FillArray_insert_key(struct FillArray_array * array_ptr, uint32_t fill_key);
//* Fill an array with fills from a single layer  
bool FillArray_fill(struct FillArray_array * array_ptr, FILE *f_src, int fill_layer);

void FillArray_report(struct FillArray_array * array_ptr);
//* Sort an array by key, ie:group all like fill`s together
void FillArray_sort(struct FillArray_array * array_ptr);

#endif //*FILLARRAY_H
