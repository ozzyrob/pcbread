#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "pad_array.h"
#include "key_array.h"
#include "track_array.h"


#define SCALE 0.0060
#define PS_UNITS 72

typedef struct PSInfo {
	void *primlist;
	int dg_size;
	int clearance;
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


bool PS2File_arc_dark ( struct PSInfo *ptr, FILE *f_dest, bool extra_width );
bool PS2File_arc_clear ( struct PSInfo *ptr, FILE *f_dest, bool extra_width );

bool PS2File_fil_dark ( struct PSInfo *ptr, FILE *f_dest, bool extra_width );
bool PS2File_fil_clear ( struct PSInfo *ptr, FILE *f_dest, bool extra_width );

bool PS2File_pad_dark ( struct PSInfo *ptr, FILE *f_dest, bool extra_width );
bool PS2File_pad_clear ( struct PSInfo *ptr, FILE *f_dest, bool extra_width );

bool PS2File_str_dark ( struct PSInfo *ptr, FILE *f_dest, bool extra_width );
bool PS2File_str_clear ( struct PSInfo *ptr, FILE *f_dest, bool extra_width );

bool PS2File_trk_dark ( struct PSInfo *ptr, FILE *f_dest, bool extra_width );
bool PS2File_trk_clear ( struct PSInfo *ptr, FILE *f_dest, bool extra_width );

bool PS2File_via_dark ( struct PSInfo *ptr, FILE *f_dest, bool extra_width );
bool PS2File_via_clear ( struct PSInfo *ptr, FILE *f_dest, bool extra_width );

bool PS2File_dgd ( struct PSInfo *ptr, FILE *f_dest, bool extra_width );

