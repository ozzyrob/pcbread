/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 */

#include "pcb.h"
#include "xy_extents.h"

/**
 * int XYExntents_arc
 * calculate max & min values allowing for half line width
 * will need to allow for radius & segments
 * logic to follow.
 */ 

int XYExntents_arc ( struct PCB_brd_info * brd, struct Primitive_arc_data * arc) {
	
	int x, y;

	x = arc->x_ref + ( arc->linewidth/2);
	y = arc->y_ref + ( arc->linewidth/2);
				
				if ( x > brd->max_x) { brd->max_x = x; }
				if ( y > brd->max_y) { brd->max_y = y; }

	x = arc->x_ref - ( arc->linewidth/2);
	y = arc->y_ref - ( arc->linewidth/2);
				
				if ( x < brd->min_x) { brd->min_x = x; }
				if ( y < brd->min_y) { brd->min_y = y; }

	return 0; 
}

/**
 * int XYExntents_fill
 * calculate min & max values
 * min & max are tested x1 & y1 , x2 & y2 
 */ 
 
int XYExntents_fill ( struct PCB_brd_info * brd, struct Primitive_fill_data * fill) {
	 
	int x, y;
//* x1,y1	
	x = fill->x1;
	y = fill->y1;
				
				if ( x > brd->max_x) { brd->max_x = x; }
				if ( y > brd->max_y) { brd->max_y = y; }
				if ( x > brd->min_x) { brd->min_x = x; }
				if ( y > brd->min_y) { brd->min_y = y; }


//* x2,x2
	x = fill->x2;
	y = fill->y2;
				
				if ( x > brd->max_x) { brd->max_x = x; }
				if ( y > brd->max_y) { brd->max_y = y; }
				if ( x > brd->min_x) { brd->min_x = x; }
				if ( y > brd->min_y) { brd->min_y = y; }

	return 0;

}

/**
 * int XYExntents_pad
 * calculate max & min values allowing for half pad width
 */ 

int XYExntents_pad ( struct PCB_brd_info * brd, struct Primitive_pad_data * pad) { 
	
	int x, y;
	
	x = pad->x_ref + ( pad->x_size/2);
	y = pad->y_ref + ( pad->y_size/2);
				
				if ( x > brd->max_x) { brd->max_x = x; }
				if ( y > brd->max_y) { brd->max_y = y; }

	x = pad->x_ref - ( pad->x_size/2);
	y = pad->y_ref - ( pad->y_size/2);
				
				if ( x < brd->min_x) { brd->min_x = x; }
				if ( y < brd->min_y) { brd->min_y = y; }
	return 0;

}

/**
 * int XYExntents_string
 * Will complete this after routines for outputting 
 * characters is devised
 * 	int x_ref
 *	int y_ref
 *	int height
 *	int rotation
 *	int linewidth
 *	int layer
 *	char *text
 */ 

int XYExntents_string ( struct PCB_brd_info * brd, struct Primitive_string_data * str) { 

	return 0;

}

/**
 * int XYExntents_track
 * calculate max & min values allowing for half line width

 */ 

int XYExntents_track ( struct PCB_brd_info * brd, struct Primitive_track_data * trk) {
	 
	int x, y;
//* x1,y1	
	x = trk->x1 + ( trk->width/2);
	y = trk->y1 + ( trk->width/2);
				
				if ( x > brd->max_x) { brd->max_x = x; }
				if ( y > brd->max_y) { brd->max_y = y; }

	x = trk->x1 - ( trk->width/2);
	y = trk->y1 - ( trk->width/2);
				
				if ( x < brd->min_x) { brd->min_x = x; }
				if ( y < brd->min_y) { brd->min_y = y; }

//* x2,x2
	x = trk->x2 + ( trk->width/2);
	y = trk->y2 + ( trk->width/2);
				
				if ( x > brd->max_x) { brd->max_x = x; }
				if ( y > brd->max_y) { brd->max_y = y; }

	x = trk->x2 - ( trk->width/2);
	y = trk->y2 - ( trk->width/2);
				
				if ( x < brd->min_x) { brd->min_x = x; }
				if ( y < brd->min_y) { brd->min_y = y; }
	return 0;

}


/**
 * int XYExntents_via
 * calculate max & min values allowing for half diameter
 */ 

int XYExntents_via ( struct PCB_brd_info * brd, struct Primitive_via_data * via) {
	 
	int x, y;
	
	x = via->x_ref + ( via->diameter/2);
	y = via->y_ref + ( via->diameter/2);
				
				if ( x > brd->max_x) { brd->max_x = x; }
				if ( y > brd->max_y) { brd->max_y = y; }

	x = via->x_ref - ( via->diameter/2);
	y = via->y_ref - ( via->diameter/2);
				
				if ( x < brd->min_x) { brd->min_x = x; }
				if ( y < brd->min_y) { brd->min_y = y; }
	return 0;

}
