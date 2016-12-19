#include <stdbool.h>

#ifndef PCBHDR_H
#define PCBHDR_H


//* Max board size 32" x 32"
#define PCB_MIN_X 0
#define PCB_MIN_Y 0
#define PCB_MAX_X 32000
#define PCB_MAX_Y 32000

#define PCB_MIN_TRACK_WIDTH 1
#define PCB_MAX_TRACK_WIDTH 255

#define PCB_NUM_ARC_VARS 6
#define PCB_NUM_FILL_VARS 5
#define PCB_NUM_PAD_VARS 8
#define PCB_NUM_STR_VARS 6
#define PCB_NUM_TRK_VARS 7
#define PCB_NUM_VIA_VARS 4
//* max value for key = 0x7FFFFE
#define PCB_MALFORMED_LINE 0x800000
#define PCB_FILL_KEY 0x800000
 
/**
 * user-routed
 * 1 user placed track
 * 0 Autorouter placed track
 */
#define PLACED_AUTO 0
#define PLACED_USER 1

/**
* segments
* n is a number with the lower 4 bits controlling the display status of the 4
* quadrants of the circle.
* Bit 0 upper right quadrant
* bit 1 upper left quadrant
* Bit 2 lower left quadrant
* bit 3 lower right quadrant
* If the bit equals 1 then the quadrant is displayed
* Therefore a segment value of 15 is a complete circle, (1111 in binary).
 */
#define SEG_UPPER_RIGHT_QUAD 0X01
#define SEG_UPPER_LEFT_QUAD 0X02
#define SEG_LOWER_LEFT_QUAD 0X04
#define SEG_LOWER_RIGHT_QUAD 0X08
#define SEG_FULL_CIRCLE 0x0F

/**
 * xsize
 * 1 to 1000
 * (width of the pad)
 * ysize
 * 1 to 1000
 * (height of the pad)
 */
#define PAD_MIN_X_SIZE 1
#define PAD_MAX_X_SIZE 1000
#define PAD_MIN_Y_SIZE 1
#define PAD_MAX_Y_SIZE 1000

/**
 * shapes
 * 1 to 6
 * 1 Circular
 * 2 Rectangle
 * 3 Octagonal
 * 4 Rounded Rectangle
 * 5 Cross Hair Target
 * 6 Moiro Target
 */
#define PAD_SHAPE_CIRC 1
#define PAD_SHAPE_RECT 2
#define PAD_SHAPE_OCT 3
#define PAD_SHAPE_RND_RECT 4
#define PAD_SHAPE_CROSS_HAIR 5
#define PAD_SHAPE_MOIRO 6
#define PAD_SHAPE_DGD 7  

/**
 * pwr/gnd
 * 1 to 5
 * 1 No Pwr/Gnd Plane Connection
 * 2 Relief to Ground Plane
 * 3 Direct to Ground Plane
 * 4 Relief to Power Plane
 * 5 Direct to Power Plane
 */
#define NC_PWR_GND 1
#define RELIEF_TO_GND 2
#define DIRECT_TO_GND 3
#define RELIEF_TO_PWR 4
#define DIRECT_TO_PWR 5

/**
 * padname
 * alphanumeric up to 4 characters in length
 * text
 * alphanumeric up to 32 characters
 */
#define PADNAME_MAX_CHAR 4
#define TEXT_MAX_CHAR 32

#define PCB_MIN_TEXT_HT 36
#define PCB_MAX_TEXT_HT 1000

/**
 * Rotation (of text)
 * Possible values are
 * 0 No Rotation
 * 1 90 Degree Rotation
 * 2 180 Degree Rotation
 * 3 270 Degree Rotation
 * 16 No Rotation Mirrored on X Axis
 * 17 90 Degree Rotation Mirrored on X
 * 18 180 Degree Rotation Mirrored on X
 * 19 270 Degree Rotation Mirrored on X
 */ 
#define ROT_NONE 0
#define ROT_90 1 
#define ROT_180 2 
#define ROT_270 3 
#define ROT_0_MIRROR 16
#define ROT_90_MIRROR 17
#define ROT_180_MIRROR 18
#define ROT_270_MIRROR 19
/**
 * Layer (of tracks, fills, arcs and strings)
 * 1 Top Layer 
 * 2 Mid Layer 1 
 * 3 Mid Layer 2 
 * 4 Mid Layer 3
 * 5 Mid Layer 4
 * 6 Bottom Layer
 * 7 Top Overlay
 * 8 Bottom Overlay
 * 9 Ground Plane Layer
 * 10 Power Plane Layer
 * 11 Board Layer
 * 12 Keep Out Layer
 * 13 Multi Layer
 */
#define TOP_LAYER 1
#define MID_1_LAYER 2
#define MID_2_LAYER 3
#define MID_3_LAYER 4
#define MID_4_LAYER 5
#define BOTTOM_LAYER 6
#define TOP_OVERLAY 7
#define BOTTOM_OVERLAY 8
#define GND_PLANE_LAYER 9
#define PWR_PLANE_LAYER 10
#define BOARD_LAYER 11
#define KEEP_OUT_LAYER 12
#define MULTI_LAYER 13

/**
 * via
 * diameter
 * 1 to 255 (mils)
 */
#define VIA_MIN_DIA 1
#define VIA_MAX_DIA 255 
 
      





//* Global struture							 
struct PCB_glb {
	bool keep_tmp;
	int status;
	char *src_filename;
	char *dest_filename;
	char *temp_filename;

};

//* Board Info
struct PCB_brd_info {

	//* in mils
	int min_x;
	int min_y;
	int max_x;
	int max_y;
	
	//* in mils
	int board_x;
	int board_y;
	
	int comp_total;
	
	int arc_total;
	int comp_arcs;
	int free_arcs;
	
	int fill_total;
	int comp_fills;
	int free_fills;
	
	int pad_total;
	int comp_pads;
	int free_pads;

	int string_total;
	int comp_strings;
	int free_strings;
	
	int track_total;
	int comp_tracks;
	int free_tracks;
	
	int via_total;
	int comp_vias;
	int free_vias;
};
	
	
#endif /* PCB_H */

