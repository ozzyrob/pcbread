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

#include <stdint.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>
#include "ps2file.h"
#include "pad_array.h"
#include "track_array.h"
#include "pcb.h"
#include "ps_strings.h"
bool PS2File_procs ( FILE *f_dest ) {
	
	fprintf(f_dest,"%s\n",CIRCPAD);
	fprintf(f_dest,"%s\n",RECTPAD);
	fprintf(f_dest,"%s\n",OCTPAD);
	fprintf(f_dest,"%s\n",XRNDRECT);
	fprintf(f_dest,"%s\n",YRNDRECT);
	fprintf(f_dest,"%s\n",XHAIR);
	fprintf(f_dest,"%s\n",MOIRO);
	fprintf(f_dest,"%s\n",TRACK);
	fprintf(f_dest,"%s\n",DGD);
	fprintf(f_dest,"%s\n",FILL);
	fprintf(f_dest,"%%%%EndProlog\n");
	
	return true;
}


bool PS2File_header ( FILE *f_dest ) {
	
	fprintf(f_dest,"%s\n",HEADER);
	return true;
}


bool PS2File_creator ( FILE *f_dest ) {
	
	fprintf(f_dest,"%s\n",CREATOR);
	return true;
}


bool PS2File_date ( FILE * f_dest ) {
		struct timeval timenow;
    struct tm *tm;
    char buff[32];
        gettimeofday(&timenow, NULL);
    tm = localtime(&timenow.tv_sec);
    
    strftime(buff,32,"%F %H:%M:%S%z", tm);
    
    fprintf(f_dest, "%%%%CreationDate: %s\n", buff);
    return true;
}


bool PS2File_title ( FILE *f_dest,  char *title_str ) {
	
	fprintf( f_dest, "%%%%Title: %s\n", title_str); 
	return true;
}

bool PS2File_translate ( FILE *f_dest, float x_pos, float y_pos ) {

	float xpos = x_pos * PS_UNITS;
	float ypos = y_pos * PS_UNITS;
	
	fprintf(f_dest, "%.4f %.4f translate\n", xpos, ypos);	
	
	return true;
}
bool PS2File_scale ( FILE *f_dest, float x_scale, float y_scale ) {

	float xscale = x_scale * SCALE;
	float yscale = y_scale * SCALE;
	
	fprintf(f_dest, "%.4f %.4f scale\n", xscale, yscale); 
	
	return true;
}


bool PS2File_linecap ( FILE *f_dest, int cap ) {
	
	fprintf(f_dest, "%d setlinecap\n", cap);
	
	return true;
}


bool PS2File_showpage ( FILE *f_dest ) {
	
	fprintf( f_dest, "showpage\n");
	
	return true;
}

bool PS2File_trk ( struct PSInfo *ptr, FILE *f_dest, bool extra_width, float fill ) {

	bool retn_val = false;
	int cur_idx = 0;
	struct TrackArray_array *track_list = ptr->primlist;
	int end_idx = track_list->used;
	int X1, Y1, X2, Y2, Width;
	int clearance;
	

	for ( cur_idx = 0; cur_idx < end_idx; cur_idx++ ) {
	
		X1 = track_list->array[cur_idx].x1 * 12;
		Y1 = track_list->array[cur_idx].y1 * 12;
		X2 = track_list->array[cur_idx].x2 * 12;
		Y2 = track_list->array[cur_idx].y2 * 12;
		clearance = ( extra_width == OVER_SIZE ) ? ( ptr->clearance * 2) : ( ptr->clearance * 0 );
		Width = ( track_list->array[cur_idx].width + clearance) * 12; 
		
		fprintf( f_dest, "%d %d %d %d %1.2f %d TRK\n", X2, Y2, X1, Y1, fill, Width);
	}
	
	retn_val = true;
	return retn_val;
}

		
bool PS2File_pad ( struct PSInfo *ptr, FILE *f_dest, bool extra_width, float fill ) {

	bool retn_val = false;
	int cur_idx = 0;
	struct PadArray_array *pad_list = ptr->primlist;
	int end_idx = pad_list->used;
	int x_ref = 0;
	int y_ref = 0;
	int x_size = 0;
	int y_size = 0;
	int shape = 0;
	int clearance = 0;
	uint32_t src_key;
	char data_line[64];

	for ( cur_idx = 0; cur_idx < end_idx; cur_idx++ ) {
		x_ref = pad_list->array[cur_idx].x_ref * 12;
		y_ref = pad_list->array[cur_idx].y_ref * 12;
		clearance = ( extra_width == OVER_SIZE ) ? ( ptr->clearance * 2 ) : ( ptr->clearance * 0 );
		src_key =  pad_list->array[cur_idx].key;
		x_size = ( ( ( src_key >> 13 ) & 0x03FF ) + clearance ) * 12;
		y_size = ( ( ( src_key >> 3 ) & 0x03FF ) + clearance ) * 12;
		shape = ( src_key & 0x07 );

		switch ( shape ) {
	
				case PAD_SHAPE_CIRC:
					sprintf(data_line, "%d %d %d %d %1.2f CIR", x_ref, y_ref, x_size, y_size, fill);
					break;

				case PAD_SHAPE_RECT:
					sprintf(data_line, "%d %d %d %d %1.2f REC", x_ref, y_ref, x_size, y_size, fill);
					break;
			
				case PAD_SHAPE_OCT:
					sprintf(data_line, "%d %d %d %d %1.2f OCT", x_ref, y_ref, x_size, y_size, fill);
					break;
			
				case PAD_SHAPE_RND_RECT:
					if ( x_size > y_size ) {
						sprintf(data_line, "%d %d %d %d %1.2f XRR", x_ref, y_ref, x_size, y_size, fill);
					}
					else {
						sprintf(data_line, "%d %d %d %d %1.2f YRR", x_ref, y_ref, x_size, y_size, fill);
					}
					break;
			
				default:
				fprintf(stderr, "Invalid shape\n");
		}
		fprintf( f_dest, "%s\n", data_line);	
	}
	
	retn_val = true;
	return retn_val;
}


bool PS2File_dgd ( struct PSInfo *ptr, FILE *f_dest, bool extra_width, float fill ) {
	
	bool retn_val = false;
	int cur_idx = 0;
	struct PadArray_array *pad_list = ptr->primlist;
	int end_idx = pad_list->used;
	int dg = ptr->dg_size;
	int diameter;
	int x_ref = 0;
	int y_ref = 0;
	int clearance = 0;

	for ( cur_idx = 0; cur_idx < end_idx; cur_idx++ ) {
		x_ref = pad_list->array[cur_idx].x_ref * 12;
		y_ref = pad_list->array[cur_idx].y_ref * 12;
		clearance = ( extra_width == OVER_SIZE ) ? ( ptr->clearance * 2 ) : ( ptr->clearance * 0 );
		diameter = ( dg + clearance ) * 12;
		fprintf( f_dest, "%d %d %d %1.2f DGD\n", x_ref, y_ref, diameter, fill);	
	}
	
	retn_val = true;
	return retn_val;
}

bool PS2File_back_ground ( struct PSInfo *psinfo , FILE *f_dest, int border, float fill) {
	
	int brd_border = (psinfo->clearance/2) + border;
	int X1 = ( psinfo->brd_x1 - brd_border )*12;
	int Y1 = ( psinfo->brd_y1 - brd_border )*12;
	int X2 = ( psinfo->brd_x2 + brd_border )*12;
	int Y2 = ( psinfo->brd_y2 + brd_border )*12;
	
	fprintf( f_dest, "%% Board background\n");
	fprintf( f_dest, "newpath\n%1.2f setgray\n", fill);
	fprintf( f_dest, "%d %d moveto\n",X1,Y1 );
	fprintf( f_dest, "%d %d lineto\n",X1,Y2 );
	fprintf( f_dest, "%d %d lineto\n",X2,Y2 );
	fprintf( f_dest, "%d %d lineto\n",X2,Y1 );
	fprintf( f_dest, "closepath fill\n");
	 
	return true;
}	 
