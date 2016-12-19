#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "pcb.h"

#ifndef PRIMITIVE_H
#define PRIMITIVE_H

/** Arcs
 * FA or CA
 * x y radius segments linewidth layer
 */
struct Primitive_arc_data {
	int x_ref;
	int y_ref;
	int radius;
	int segments;
	int linewidth;
	int layer;
};
/** Fills
 * FF or CF
 * x1 y1 x2 y2 layer
 */
struct Primitive_fill_data {
	int x1;
	int y1;
	int x2;
	int y2;
	int layer;
};

/** Pads
 * FP or CP
 * x y xsize ysize shape holesize pwr/gnd layer
 * padname
 */
struct Primitive_pad_data {
	int x_ref;
	int y_ref;
	int x_size;
	int y_size;
	int shape;
	int hole_size;
	int pwr_gnd;
	int layer;
	char pad_name[6];
};
/** Strings
 * FS or CS
 * x y height rotation linewidth layer
 * text
 */
struct Primitive_string_data {
	int x_ref;
	int y_ref;
	int height;
	int rotation;
	int linewidth;
	int layer;
	char text[33]; 
};


/** Tracks
 * FT or CT
 * x1 y1 x2 y2 width layer user-routed
 */
struct Primitive_track_data {
	int x1;
	int y1;
	int x2;
	int y2;
	int width;
	int layer;
	int user_routed;
};

/** Vias
 * FV or CV
 * x y diameter holesize
 */
struct Primitive_via_data {
	int x_ref;
	int y_ref;
	int diameter;
	int hole_size;
};

uint32_t Primitive_parse_arc (char * src, struct Primitive_arc_data * ptr);
uint32_t Primitive_parse_pad(char * src, struct Primitive_pad_data * ptr);
uint32_t Primitive_parse_string (char * src, struct Primitive_string_data * ptr);
uint32_t Primitive_parse_track (char * src, struct Primitive_track_data * ptr);
uint32_t Primitive_parse_via (char * src, struct Primitive_via_data * ptr);

#endif /* PRIMITIVE_H */
