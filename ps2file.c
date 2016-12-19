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
	
	fprintf(f_dest, "%f %f translate\n", xpos, ypos);	
	
	return true;
}
bool PS2File_scale ( FILE *f_dest, float x_scale, float y_scale ) {

	float xscale = x_scale * SCALE;
	float yscale = y_scale * SCALE;
	
	fprintf(f_dest, "%f %f scale\n", xscale, yscale); 
	
	return true;
}


bool PS2File_linecap ( FILE *f_dest, int cap ) {
	
	fprintf(f_dest, "%d setlinecap\n", cap);
	
	return true;
}
	
bool PS2File_trk_dark ( struct PSInfo *ptr, FILE *f_dest, bool extra_width ) {

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
		clearance = ( extra_width == true ) ? ( ptr->clearance * 2) : ( ptr->clearance * 0 );
		Width = ( track_list->array[cur_idx].width + clearance) * 12; 
		
		fprintf( f_dest, "%d %d %d %d 0.00 %d TRACK\n", X2, Y2, X1, Y1, Width);
	}
	
	retn_val = true;
	return retn_val;
}


bool PS2File_trk_clear ( struct PSInfo *ptr, FILE *f_dest, bool extra_width ) {

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
		clearance = ( extra_width == true ) ? ( ptr->clearance * 2) : ( ptr->clearance * 0 );
		Width = ( track_list->array[cur_idx].width + clearance) * 12; 
		
		fprintf( f_dest, "%d %d %d %d 1.00 %d TRACK\n", X2, Y2, X1, Y1, Width);
	}
	
	retn_val = true;
	return retn_val;
}


bool PS2File_pad_dark ( struct PSInfo *ptr, FILE *f_dest, bool extra_width ) {

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
		clearance = ( extra_width == true ) ? ( ptr->clearance * 2 ) : ( ptr->clearance * 0 );
		src_key =  pad_list->array[cur_idx].key;
		x_size = ( ( ( src_key >> 13 ) & 0x03FF ) + clearance ) * 12;
		y_size = ( ( ( src_key >> 3 ) & 0x03FF ) + clearance ) * 12;
		shape = ( src_key & 0x07 );

		switch ( shape ) {
	
				case PAD_SHAPE_CIRC:
					sprintf(data_line, "%d %d %d %d 0.00 CIRCPAD", x_ref, y_ref, x_size, y_size);
					break;

				case PAD_SHAPE_RECT:
					sprintf(data_line, "%d %d %d %d 0.00 RECTPAD", x_ref, y_ref, x_size, y_size);
					break;
			
				case PAD_SHAPE_OCT:
					sprintf(data_line, "%d %d %d %d 0.00 OCTPAD", x_ref, y_ref, x_size, y_size);
					break;
			
				case PAD_SHAPE_RND_RECT:
					if ( x_size > y_size ) {
						sprintf(data_line, "%d %d %d %d 0.00 XRNDRECT", x_ref, y_ref, x_size, y_size);
					}
					else {
						sprintf(data_line, "%d %d %d %d 0.00 YRNDRECT", x_ref, y_ref, x_size, y_size);
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
		
		
bool PS2File_pad_clear ( struct PSInfo *ptr, FILE *f_dest, bool extra_width ) {

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
		clearance = ( extra_width == true ) ? ( ptr->clearance * 2 ) : ( ptr->clearance * 0 );
		src_key =  pad_list->array[cur_idx].key;
		x_size = ( ( ( src_key >> 13 ) & 0x03FF ) + clearance ) * 12;
		y_size = ( ( ( src_key >> 3 ) & 0x03FF ) + clearance ) * 12;
		shape = ( src_key & 0x07 );

		switch ( shape ) {
	
				case PAD_SHAPE_CIRC:
					sprintf(data_line, "%d %d %d %d 1.00 CIRCPAD", x_ref, y_ref, x_size, y_size);
					break;

				case PAD_SHAPE_RECT:
					sprintf(data_line, "%d %d %d %d 1.00 RECTPAD", x_ref, y_ref, x_size, y_size);
					break;
			
				case PAD_SHAPE_OCT:
					sprintf(data_line, "%d %d %d %d 1.00 OCTPAD", x_ref, y_ref, x_size, y_size);
					break;
			
				case PAD_SHAPE_RND_RECT:
					if ( x_size > y_size ) {
						sprintf(data_line, "%d %d %d %d 1.00 XRNDRECT", x_ref, y_ref, x_size, y_size);
					}
					else {
						sprintf(data_line, "%d %d %d %d 1.00 YRNDRECT", x_ref, y_ref, x_size, y_size);
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

		
bool PS2File_dgd ( struct PSInfo *ptr, FILE *f_dest, bool extra_width ) {
	
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
		clearance = ( extra_width == true ) ? ( ptr->clearance * 2 ) : ( ptr->clearance * 0 );
		diameter = ( dg + clearance ) * 12;
		fprintf( f_dest, "%d %d %d 0.00 DGD\n", x_ref, y_ref, diameter);	
	}
	
	retn_val = true;
	return retn_val;
}

