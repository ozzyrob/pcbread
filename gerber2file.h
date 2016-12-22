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

typedef struct GbrInfo {
	void *primlist;
	void *keylist;
	int dg_size;
	char dcode_str[8];
}gbrInfo_t;

bool Gerber2File_Get_Dcode ( struct GbrInfo *ptr, uint32_t key );
bool Gerber2File_OpCode_dgd ( struct GbrInfo *ptr, FILE *f_dest );
bool Gerber2File_OpCode_pad ( struct GbrInfo *ptr, FILE *f_dest );
bool Gerber2File_OpCode_track ( struct GbrInfo *ptr, FILE *f_dest );
bool Gerber2File_Apt_Dict ( struct GbrInfo *ptr, FILE *f_dest );
bool Wirte2File_Layer_Dark (FILE * f_dest);
bool Wirte2File_Layer_Clear (FILE * f_dest);
bool Wirte2File_Units_Inch (FILE * f_dest);
bool Wirte2File_M02_EOF (FILE * f_dest);
bool Wirte2File_Image_Pos (FILE * f_dest);
bool Wirte2File_Image_Neg (FILE * f_dest);
bool Wirte2File_Format_Info (FILE * f_dest);
bool Wirte2File_Date_Stamp (FILE * f_dest);

bool Gerber2File_Get_Dcode_Clearance ( struct GbrInfo *ptr, uint32_t key );
bool Gerber2File_Apt_Dict_Pour_Clearance( struct GbrInfo *ptr, FILE *f_dest );
bool Gerber2File_OpCode_pad_clearance ( struct GbrInfo *ptr, FILE *f_dest );
bool Gerber2File_OpCode_track_clearance ( struct GbrInfo *ptr, FILE *f_dest );

 
