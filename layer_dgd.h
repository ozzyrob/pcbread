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
