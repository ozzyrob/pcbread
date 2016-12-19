#include "pcb.h"
#include "primitive.h"

/**
 * Primitive_parse_arc
 * 
 */
uint32_t Primitive_parse_arc (char * src, struct Primitive_arc_data * ptr) {
	
	int num_of_vars;	
	
	num_of_vars = sscanf(src, "%5d%5d%5d%2d%3d%2d", &ptr->x_ref, &ptr->y_ref, &ptr->radius, &ptr->segments, &ptr->linewidth, &ptr->layer);
	if ( num_of_vars != PCB_NUM_ARC_VARS ) {
		fprintf(stderr, "Malformed line\n");
		return PCB_MALFORMED_LINE;
	}

return 0;
} //* Primitive_parse_arc

/**
 * PrimitiveGet_pad
 * 
 */
uint32_t Primitive_parse_pad(char * src, struct Primitive_pad_data * ptr) {
	
	int num_of_vars;

	num_of_vars = sscanf(src, "%5d%5d%4d%4d%1d%4d%1d%2d", &ptr->x_ref, &ptr->y_ref, &ptr->x_size, &ptr->y_size, &ptr->shape, &ptr->hole_size, &ptr->pwr_gnd, &ptr->layer);
	if ( num_of_vars != PCB_NUM_PAD_VARS ) {
		fprintf(stderr, "Malformed line\n");
		return PCB_MALFORMED_LINE;
	}

return 0;
} //* Primitive_parse_pad

/**
 * Primitive_parse_string
 * 
 */
uint32_t Primitive_parse_string (char * src, struct Primitive_string_data * ptr) {
	
	int num_of_vars;

	num_of_vars = sscanf(src, "%5d%5d%4d%2d%3d%2d", &ptr->x_ref, &ptr->y_ref, &ptr->height, &ptr->rotation, &ptr->linewidth, &ptr->layer);
	if ( num_of_vars != PCB_NUM_STR_VARS ) {
		fprintf(stderr, "Malformed line\n");
		return PCB_MALFORMED_LINE;
	}

return 0;
} //* Primitive_parse_string

/**
 * Primitive_parse_track
 * 
 */
uint32_t Primitive_parse_track (char * src, struct Primitive_track_data * ptr) {
	
	int num_of_vars;

	num_of_vars = sscanf(src, "%5d%5d%5d%5d%4d%2d%1d", &ptr->x1, &ptr->y1, &ptr->x2, &ptr->y2, &ptr->width, &ptr->layer, &ptr->user_routed);
	if ( num_of_vars != PCB_NUM_TRK_VARS ) {
		fprintf(stderr, "Malformed line\n");
		return PCB_MALFORMED_LINE;
	}

return 0;
} //* Primitive_parse_track

/**
 * Primitive_parse_via
 * 
 */
uint32_t Primitive_parse_via (char * src, struct Primitive_via_data * ptr) {
	
	int num_of_vars;
	 
	num_of_vars = sscanf(src, "%5d%5d%3d%3d", &ptr->x_ref, &ptr->y_ref, &ptr->diameter, &ptr->hole_size);
	if ( num_of_vars != PCB_NUM_VIA_VARS ) {
		fprintf(stderr, "Malformed line\n");
		return PCB_MALFORMED_LINE;
	}

return 0;
} //* Primitive_parse_via

