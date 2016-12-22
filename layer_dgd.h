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

typedef struct DGD_Info {
	char *filename;
	void *prim_lst;
	void *keylist;
	int dg_size;
	char *aptdef_str;
	char dcode_str[8];
}dgdinfo_t;

//* 12-12-2016:
//* Need function to write data to file that requires Drill guide written
//* as clear not as seperate file.
bool LayerDGD_Output_to_File ( struct DGD_Info *dgdinfo);
bool LayerDGD_Header_to_File ( FILE *f_dest );
bool LayerDGD_AptDict_to_file ( FILE *f_dest, char *aptdef );
bool LayerDGD_OpCode_to_File ( FILE *f_dest, struct PadArray_array *pad_list, char * dcode );
bool LayerDGD_M02_to_File ( FILE *f_dest );
bool LayerDGD_Get_Dcode ( struct DGD_Info *ptr );
//* bool LayerDGD_Append_to_File ( FILE *f_dest,  DGD_Info *dgdinfo);
