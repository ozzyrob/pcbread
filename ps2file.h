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

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "pad_array.h"
#include "key_array.h"
#include "track_array.h"


#define SCALE 0.0060
#define PS_UNITS 72
#define WHITE 1.00
#define GREY 0.50
#define GRAY 0.50
#define BLACK 0.00
#define CLEAR 1.00
#define DARK 0.00
#define OVER_SIZE true
#define ORIG_SIZE false

typedef struct PSInfo {
	void *primlist;
	int dg_size;
	int clearance;
	int brd_x1, brd_y1, brd_x2, brd_y2;
}psInfo_t;

bool PS2File_header ( FILE *f_dest );
bool PS2File_creator ( FILE *f_dest);
bool PS2File_date ( FILE * f_dest );
bool PS2File_procs ( FILE *f_dest );
bool PS2File_title ( FILE *f_dest,  char *title_str );
bool PS2File_paper ( FILE *f_dest );
bool PS2File_comment ( FILE *f_dest, char *comment_str );
bool PS2File_gsave ( FILE *f_dest );
bool PS2File_grestore ( FILE *f_dest );
bool PS2File_showpage ( FILE *f_dest );
bool PS2File_translate ( FILE *f_dest, float x_pos, float y_pos );
bool PS2File_scale ( FILE *f_dest, float x_scale, float y_scale );
bool PS2File_clip ( FILE *f_dest, float x1, float y1, float x2, float y2 );
bool PS2File_linecap ( FILE *f_dest, int cap );

bool PS2File_begin_brd_proc ( FILE *f_dest, char *board_str );
bool PS2File_end_brd_proc ( FILE *f_dest );

bool PS2File_back_ground ( struct PSInfo *psinfo, FILE *f_dest, int border, float fill); 

bool PS2File_arc ( struct PSInfo *ptr, FILE *f_dest, bool extra_width, float fill );

bool PS2File_fil ( struct PSInfo *ptr, FILE *f_dest, bool extra_width, float fill );

bool PS2File_pad ( struct PSInfo *ptr, FILE *f_dest, bool extra_width, float fill );

bool PS2File_str ( struct PSInfo *ptr, FILE *f_dest, bool extra_width, float fill );

bool PS2File_trk ( struct PSInfo *ptr, FILE *f_dest, bool extra_width, float fill );

bool PS2File_via ( struct PSInfo *ptr, FILE *f_dest, bool extra_width, float fill );

bool PS2File_dgd ( struct PSInfo *ptr, FILE *f_dest, bool extra_width, float fill );


