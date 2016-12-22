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
#include "layer_dgd.h"
#include "pad_array.h"
#include "pcb.h"


/**
 *  LayerDGD_Output_to_File:
 *  Write drill guide to output file
 */
bool LayerDGD_Output_to_File ( struct DGD_Info *dgdinfo) {
	
	bool retn_val = false;
	FILE * f_dest;
	//*int dcode_idx;
	//* Output
	/* Attempt to open the output file in read\write mode */
	/*	(no appending is done, any existing file will be */
	/*	overwritten */
	f_dest = fopen(dgdinfo->filename,"w+");
	if (!f_dest) {
		fprintf(stderr,"Error: Cannot open output file '%s' for read\\write (%s)\n", dgdinfo->filename, strerror(errno));
		return false;
	}
	
    LayerDGD_Get_Dcode ( dgdinfo );
	LayerDGD_Header_to_File( f_dest );
	LayerDGD_AptDict_to_file( f_dest, dgdinfo->aptdef_str);
	LayerDGD_OpCode_to_File ( f_dest, dgdinfo->prim_lst, dgdinfo->dcode_str );
	LayerDGD_M02_to_File ( f_dest );		
	retn_val = true;
	return retn_val;
}


/**
 * LayerDGD_Header_to_File:
 * create header & write to file
 */
bool LayerDGD_Header_to_File ( FILE * f_dest ) {
	
	bool retn_val = false;
	fprintf(f_dest,"G04 #@ TF.FileFunction,Drillguide,L13,All,Signal*\n");
	fprintf(f_dest,"%%FSLAX23Y23*%%\n");
	fprintf(f_dest,"G04 Gerber Fmt 2.3, Leading zero omitted, Abs format (unit inch)*\n");
	fprintf(f_dest,"G04 Created by pcbread *\n");
	fprintf(f_dest,"%%MOIN*%%\n");
	
	retn_val = true;
	return retn_val;
}


/**
 * LayerDGD_AptDict_to_file:
 * create & write apterture dictionary to file
 */
bool LayerDGD_AptDict_to_file ( FILE * f_dest, char *aptdef ) {
	
	bool retn_val = false;

	fprintf(f_dest, "G04 START APERTURE LIST*\n");
	fprintf(f_dest, "%s\n", aptdef);
	fprintf(f_dest, "G04 END APERTURE LIST*\n");
	
	retn_val = true;
	return retn_val;
}


/**
 * LayerDGD_OpCode_to_File:
 * create & write list of co-ords with flash code (D3) to file
 */
bool LayerDGD_OpCode_to_File ( FILE * f_dest, struct PadArray_array *pad_list, char * dcode ) {
	
	bool retn_val = false;
	int cur_idx = 0;
	int end_idx = pad_list->used;
	
	fprintf(f_dest, "G04 START DILL GUIDE LIST*\n");
	fprintf(f_dest, "%s*\n", dcode);
	
	for ( cur_idx = 0; cur_idx < end_idx; cur_idx++ ) {
	
	fprintf( f_dest, "X%dY%dD03*\n", pad_list->array[cur_idx].x_ref, pad_list->array[cur_idx].y_ref);
	}
	
	fprintf(f_dest, "G04 END DILL GUIDE LIST*\n");
	
	retn_val = true;
	return retn_val;
}


/**
 * LayerDGD_M02_to_File
 * terminate file with end-of-file command (M02)
 */
bool LayerDGD_M02_to_File ( FILE * f_dest ) {
	
	bool retn_val = false;
	
	fprintf( f_dest, "M02*\n");
	
	retn_val = true;
	return retn_val;
}
/**
 *  LayerDGD_Get_Dcode:
 *  get apterture def string
 *  and create dcode string
 */
bool LayerDGD_Get_Dcode ( struct DGD_Info *ptr ) {  
	
	int idx;
	
	struct KeyArray_array *keys = ptr->keylist;
	
	uint32_t key = ( ( ptr->dg_size << 13 ) | ( ptr->dg_size << 3) | PAD_SHAPE_DGD );
	
	
	if ( ! KeyArray_search_key( ptr->keylist, key, &idx) ) {
		fprintf(stderr, "No Match\n");
		return false;
	}

	sprintf(ptr->dcode_str, "D%d", idx+10);
	//* ptr->aptdef_str = strdup(ptr->keylist->array[idx].definition);
	ptr->aptdef_str = keys->array[idx].definition;
	return true;
}	
