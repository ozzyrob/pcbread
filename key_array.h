#include <stdbool.h>
#include <stdint.h>

#ifndef KEYARRAY_H
#define KEYARRAY_H

struct KeyArray_aperture {
	uint32_t key;
	char definition[32];
	char pour_def[32];
};

/**
 * key & definition string are stored
 */  
struct KeyArray_array {
  struct KeyArray_aperture *array;	
  size_t used;
  size_t size;
  int pour_clearance;
};

void KeyArray_init(struct KeyArray_array * array_ptr, size_t initialSize);
void KeyArray_insert_key(struct KeyArray_array * array_ptr, uint32_t element);
void KeyArray_free(struct KeyArray_array * array_ptr);
bool KeyArray_search_key(struct KeyArray_array * array_ptr, uint32_t element, int * idx_match);
bool KeyArray_insert_key_unique(struct KeyArray_array * array_ptr, uint32_t element);

#endif //*KEYARRAY_H
