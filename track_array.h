#include <stdbool.h>
#include <stdint.h>


#ifndef TRACKARRAY_H
#define TRACKARRAY_H


 struct TrackArray_data {

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
struct TrackArray_array {
  struct TrackArray_data  *array;	
  size_t used;
  size_t size;
};

void TrackArray_init(struct TrackArray_array * array_ptr, size_t initialSize);
void TrackArray_free(struct TrackArray_array * array_ptr);
void TrackArray_insert_key(struct TrackArray_array * array_ptr, uint32_t track_key);
//* Fill an array with tracks from a single layer  
bool TrackArray_fill(struct TrackArray_array * array_ptr, FILE *f_src, int track_layer);

void TrackArray_report(struct TrackArray_array * array_ptr);
//* Sort an array by key, ie:group all like tracks together
void TrackArray_sort(struct TrackArray_array * array_ptr);

#endif //*TRACKARRAY_H
