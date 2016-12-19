#include <stdbool.h>
#include <stdint.h>


#ifndef STRARRAY_H
#define STRARRAY_H


 struct StrArray_data {
 	int x_ref;
	int y_ref;
	int height;
	int rotation;
	int width;
	int layer;
	char str_text[33];
	uint32_t key;
};

  
/**
 * key & definition string are stored
 */  
struct StrArray_array {
  struct StrArray_data  *array;	
  size_t used;
  size_t size;
};

void StrArray_init(struct StrArray_array * array_ptr, size_t initialSize);
void StrArray_free(struct StrArray_array * array_ptr);
void StrArray_insert_key(struct StrArray_array * array_ptr, uint32_t str_key);
//* Fill an array with strs from a single layer  
bool StrArray_fill(struct StrArray_array * array_ptr, FILE *f_src, int str_layer);

void StrArray_report(struct StrArray_array * array_ptr);
//* Sort an array by key, ie:group all like strs together
void StrArray_sort(struct StrArray_array * array_ptr);

#endif //*STRARRAY_H
