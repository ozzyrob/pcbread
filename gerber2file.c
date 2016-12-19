#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>
#include "gerber2file.h"
#include "pad_array.h"
#include "track_array.h"
#include "pcb.h"

/**
 *  Gerber2File_OpCode_dgd:
 *  write list of drill guides to file
 */
bool Gerber2File_OpCode_dgd ( struct GbrInfo *ptr, FILE *f_dest ) {
	
	bool retn_val = false;
	int cur_idx = 0;
	struct PadArray_array *pad_list = ptr->primlist;
	int end_idx = pad_list->used;
	
	uint32_t currkey = ( ( ptr->dg_size << 13 ) | ( ptr->dg_size << 3) | PAD_SHAPE_DGD );
	Gerber2File_Get_Dcode(ptr, currkey);	
	
	fprintf(f_dest, "G04 START DILL GUIDE LIST*\n");
	fprintf(f_dest, "%s*\n", ptr->dcode_str);
	
	for ( cur_idx = 0; cur_idx < end_idx; cur_idx++ ) {
	
	fprintf(f_dest, "X%dY%dD03*\n", pad_list->array[cur_idx].x_ref, pad_list->array[cur_idx].y_ref);
	}
	
	fprintf(f_dest, "G04 END DILL GUIDE LIST*\n");
	
	retn_val = true;
	return retn_val;
}

/**
 *  Gerber2File_OpCode_pad:
 *  write list of drill guides to file
 */
bool Gerber2File_OpCode_pad ( struct GbrInfo *ptr, FILE *f_dest ) {
	
	bool retn_val = false;
	int cur_idx = 0;
	struct PadArray_array *pad_list = ptr->primlist;
	int end_idx = pad_list->used;
	uint32_t currkey = 0;
	uint32_t prevkey = 0;
	
	
	
	fprintf(f_dest, "G04 START PAD LIST*\n");
	
	for ( cur_idx = 0; cur_idx < end_idx; cur_idx++ ) {
		
		currkey = pad_list->array[cur_idx].key;

			if ( currkey != prevkey ) {
				Gerber2File_Get_Dcode(ptr, currkey);
				prevkey = currkey;
				fprintf(f_dest, "%s*\n", ptr->dcode_str);
			}				
	
	fprintf(f_dest, "X%dY%dD03*\n", pad_list->array[cur_idx].x_ref, pad_list->array[cur_idx].y_ref);
	}
	
	fprintf(f_dest, "G04 END PAD LIST*\n");
	
	retn_val = true;
	return retn_val;
}


/**
 *  Gerber2File_OpCode_track:
 *  write list of drill guides to file
 */
bool Gerber2File_OpCode_track( struct GbrInfo *ptr, FILE *f_dest ) {
	
	bool retn_val = false;
	int cur_idx = 0;
	struct TrackArray_array *track_list = ptr->primlist;
	int end_idx = track_list->used;
	uint32_t currkey = 0;
	uint32_t prevkey = 0;
	
	
	
	fprintf(f_dest, "G04 START TRACK LIST*\n");
	
	for ( cur_idx = 0; cur_idx < end_idx; cur_idx++ ) {
		
		currkey = track_list->array[cur_idx].key;

			if ( currkey != prevkey ) {
				Gerber2File_Get_Dcode(ptr, currkey);
				prevkey = currkey;
				fprintf(f_dest, "%s*\n", ptr->dcode_str);
			}				
	
	fprintf(f_dest, "X%dY%dD02*\n", track_list->array[cur_idx].x1, track_list->array[cur_idx].y1);
	fprintf(f_dest, "X%dY%dD01*\n", track_list->array[cur_idx].x2, track_list->array[cur_idx].y2);
	
	}
	
	fprintf(f_dest, "G04 END TRACK LIST*\n");
	
	retn_val = true;
	return retn_val;
}
bool Gerber2File_Apt_Dict ( struct GbrInfo *ptr, FILE *f_dest ) {
	
	int index = 0;
	struct KeyArray_array *key_list = ptr->keylist;	

	fprintf(f_dest, "G04 START APERTURE DICTIONARY*\n");
	
	for ( index=0; index < key_list->used; index++ ) {
		fprintf(f_dest,"%s\n", key_list->array[index].definition);
	}

	fprintf(f_dest, "G04 END APERTURE DICTIONARY*\n");
	


	return true;
}
bool Wirte2File_Layer_Dark (FILE * f_dest) {
	
	fprintf(f_dest,"%%LPD*%%\n");
	
	return true;
}

bool Wirte2File_Layer_Clear (FILE * f_dest) {
	
	fprintf(f_dest,"%%LPC*%%\n");
	
	return true;
}

bool Wirte2File_Units_Inch (FILE * f_dest) {
	
	fprintf(f_dest,"%%MOIN*%%\n");
	
	return true;
}


bool Wirte2File_M02_EOF (FILE * f_dest) {
	
	fprintf(f_dest,"M02\n");
	
	return true;
}


bool Wirte2File_Image_Pos (FILE * f_dest) {
	
	fprintf(f_dest,"%%IPPOS*%%\n");
	
	return true;
}


bool Wirte2File_Image_Neg (FILE * f_dest) {
	
	fprintf(f_dest,"%%IPNEG*%%\n");
	
	return true;
}


bool Wirte2File_Format_Info (FILE * f_dest) {
	
	fprintf(f_dest,"%%FSLAX23Y23*%%\n");
	
	return true;
}

bool Wirte2File_Date_Stamp (FILE * f_dest) {
	
	struct timeval timenow;
    struct tm *tm;
    char buff[32];
    
    gettimeofday(&timenow, NULL);
    tm = localtime(&timenow.tv_sec);
    
    strftime(buff,32,"%FT%H:%M:%S%z", tm);
    
    fprintf(f_dest, "%%TF.CreationDate,%s*%%\n", buff);
    
    return true;
}


/**
 *  Gerber2File_Get_Dcode:
 *  and create dcode string
 */
bool Gerber2File_Get_Dcode ( struct GbrInfo *ptr, uint32_t key ) {  
	
	int idx;
	struct KeyArray_array * list = ptr->keylist;
	int dcode;
				
	if ( ! KeyArray_search_key( list, key, &idx) ) {
		fprintf(stderr, "No Match\n");
		return false;
	}

	sscanf(list->array[idx].definition, "%%ADD%i", &dcode);
	sprintf(ptr->dcode_str, "D%d", dcode );
	return true;
}


//******************Clearance routines*********************************
/**
 *  Gerber2File_Get_Dcode:
 *  and create dcode string
 */
bool Gerber2File_Get_Dcode_Clearance ( struct GbrInfo *ptr, uint32_t key ) {  
	
	int idx;
	struct KeyArray_array * list = ptr->keylist;
	int dcode;
			
	if ( ! KeyArray_search_key( list, key, &idx) ) {
		fprintf(stderr, "No Match\n");
		return false;
	}
	sscanf(list->array[idx].pour_def, "%%ADD%i", &dcode);
	sprintf(ptr->dcode_str, "D%d", dcode );
	return true;
}


bool Gerber2File_Apt_Dict_Pour_Clearance( struct GbrInfo *ptr, FILE *f_dest ) {
	
	int index = 0;
	struct KeyArray_array *key_list = ptr->keylist;	

	fprintf(f_dest, "G04 START CLEARANCE APERTURE DICTIONARY*\n");
	
	for ( index=0; index < key_list->used-1; index++ ) {
		fprintf(f_dest,"%s\n", key_list->array[index].pour_def);
	}

	fprintf(f_dest, "G04 END CLEARANCE APERTURE DICTIONARY*\n");
	


	return true;
}


/**
 *  Gerber2File_OpCode_pad:
 *  write list of drill guides to file
 */
bool Gerber2File_OpCode_pad_clearance ( struct GbrInfo *ptr, FILE *f_dest ) {
	
	bool retn_val = false;
	int cur_idx = 0;
	struct PadArray_array *pad_list = ptr->primlist;
	int end_idx = pad_list->used;
	uint32_t currkey = 0;
	uint32_t prevkey = 0;
	
	
	
	fprintf(f_dest, "G04 START PAD CLEARANCE LIST*\n");
	
	for ( cur_idx = 0; cur_idx < end_idx; cur_idx++ ) {
		
		currkey = pad_list->array[cur_idx].key;

			if ( currkey != prevkey ) {
				Gerber2File_Get_Dcode_Clearance(ptr, currkey);
				prevkey = currkey;
				fprintf(f_dest, "%s*\n", ptr->dcode_str);
			}				
	
	fprintf(f_dest, "X%dY%dD03*\n", pad_list->array[cur_idx].x_ref, pad_list->array[cur_idx].y_ref);
	}
	
	fprintf(f_dest, "G04 END PAD CLEARANCE LIST*\n");
	
	retn_val = true;
	return retn_val;
}


/**
 *  Gerber2File_OpCode_track:
 *  write list of drill guides to file
 */
bool Gerber2File_OpCode_track_clearance( struct GbrInfo *ptr, FILE *f_dest ) {
	
	bool retn_val = false;
	int cur_idx = 0;
	struct TrackArray_array *track_list = ptr->primlist;
	int end_idx = track_list->used;
	uint32_t currkey = 0;
	uint32_t prevkey = 0;
	
	
	
	fprintf(f_dest, "G04 START TRACK CLEARANCE LIST*\n");
	
	for ( cur_idx = 0; cur_idx < end_idx; cur_idx++ ) {
		
		currkey = track_list->array[cur_idx].key;

			if ( currkey != prevkey ) {
				Gerber2File_Get_Dcode_Clearance(ptr, currkey);
				prevkey = currkey;
				fprintf(f_dest, "%s*\n", ptr->dcode_str);
			}				
	
	fprintf(f_dest, "X%dY%dD02*\n", track_list->array[cur_idx].x1, track_list->array[cur_idx].y1);
	fprintf(f_dest, "X%dY%dD01*\n", track_list->array[cur_idx].x2, track_list->array[cur_idx].y2);
	
	}
	
	fprintf(f_dest, "G04 END TRACK CLEARANCE LIST*\n");
	
	retn_val = true;
	return retn_val;
}
