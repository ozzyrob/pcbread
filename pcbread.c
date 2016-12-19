/**
  * pcbread - read protel autotrax *.pcb
  *
  * Written and maintained by Robert Murphy [ robert.murphy@gmx.com ]
  *
  * The purpose of this program is to read autotrax *.pcb file
  *
  * Code logic based on hpgl-distiller by Paul L Daniels
  * 
  * Original version written: Tuesday 22 Nov 2016
  *
  *
  * Process description:
  *
  * pcbread -i src_filenam -o dest_filename
  *
**/
  
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
#include "mydefs.h"
#include "pcb.h"
#include "enc_key.h"
#include "mystrings.h"
#include "primitive.h"
#include "xy_extents.h"
#include "aperture.h"
#include "key_array.h"
#include "apt_dict.h"
#include "pad_array.h"
#include "track_array.h"
#include "gerber2file.h"
#include "arc_array.h"
#include "via_array.h"
#include "fill_array.h"
#include "str_array.h"
#include "ps2file.h"



#define PCB_VERSION "0.0.1"

int PCB_show_version( struct PCB_glb *glb );
int PCB_show_help( struct PCB_glb *glb );
int PCB_parse_cmdline_parameters( int argc, char **argv, struct PCB_glb *glb );
int PCB_init_global( struct PCB_glb *dest );
int PCB_init_board_info( struct PCB_brd_info * dest );
int PCB_sanitise_src( FILE* f_src, FILE* f_dest);
int PCB_validate_src (FILE * f_src);
int PCB_collect_board_information (FILE *f_src, struct PCB_brd_info *src, struct KeyArray_array *apt_keys );
int PCB_report_brd_info (struct PCB_brd_info *src );

/**
  * pcbread,  main body
  *
  * Take Protel Autotrax *.pcb and outputs gerber	
  */


int main(int argc, char **argv) {

	struct PCB_glb glb;
	struct PCB_brd_info board_info;
	struct KeyArray_array apt_keys;
	struct PadArray_array pads;
	struct TrackArray_array tracks;
	struct ArcArray_array arcs;
	struct FillArray_array fills;
	struct StrArray_array strs;
	
	struct GbrInfo priminfo;
	struct PSInfo psinfo;
	FILE *f_source, *f_destination, *f_sanitised, *f_psfile;
	
	/* Initialize our global & board data structures */
	PCB_init_global(&glb);
	PCB_init_board_info(&board_info);

	/* Parse & decypher the command line parameters provided */
	PCB_parse_cmdline_parameters(argc, argv, &glb);
	
	/* Check the fundamental sanity of the variables in
		the global data structure to ensure that we can
		actually perform some meaningful work
		*/
	if ((glb.src_filename == NULL)) {
		fprintf(stderr,"Error: No input filename given.\n");
		exit(1);
	}
	if ((glb.dest_filename == NULL)) {
		fprintf(stderr,"Error: No output filename given.\n");
		exit(1);
	}
	if ((glb.temp_filename == NULL)) {
		fprintf(stderr,"Error: Output filename is NULL.\n");
		exit(1);
	}	

//* Input		
	/* Attempt to open input file as read only */ 
	f_source = fopen(glb.src_filename,"r");
	if (!f_source) {
		fprintf(stderr,"Error: Cannot open input file '%s' for reading (%s)\n", glb.src_filename, strerror(errno));
		return ERR_NOT_OPEN_INPUT;
	}

//* Output
	/* Attempt to open the output file in read\write mode */
	/*	(no appending is done, any existing file will be */
	/*	overwritten */
	f_destination = fopen(glb.dest_filename,"w+");
	if (!f_destination) {
		fprintf(stderr,"Error: Cannot open output file '%s' for read\\write (%s)\n", glb.dest_filename, strerror(errno));
		return ERR_NOT_OPEN_OUTPUT;
	}
	
//* Temporary
	/* Attempt to open the temporary file in read\write mode */
	/*	(no appending is done, any existing file will be */
	/*	overwritten */
	f_sanitised = fopen(glb.temp_filename,"w+");
	if (!f_sanitised) {
		fprintf(stderr,"Error: Cannot open temporary file '%s' for read\\write (%s)\n", glb.temp_filename, strerror(errno));
		return ERR_NOT_OPEN_TEMP;
	}

//* Temporary
	/* Attempt to open the temporary file in read\write mode */
	/*	(no appending is done, any existing file will be */
	/*	overwritten */
	f_psfile = fopen("output.ps","w+");
	if (!f_sanitised) {
		fprintf(stderr,"Error: Cannot open  PS file '%s' for read\\write (%s)\n", "output.ps", strerror(errno));
		return ERR_NOT_OPEN_TEMP;
	}
		
	PCB_sanitise_src( f_source, f_sanitised);	
	PCB_validate_src( f_sanitised);

	//* Init Key array
	KeyArray_init( &apt_keys, 1);
	apt_keys.pour_clearance = 20;

	//* Collects statistics and saves aperture keys
	PCB_collect_board_information( f_sanitised, &board_info, &apt_keys );
	PCB_report_brd_info( &board_info );
	//*fprintf(stderr, "Apterture Array size is %d\n", apt_keys.used);
	
	//* Fill definition fields for all members
	//* Plus Drill guide	
	AptDict_fill(&apt_keys, 20);
	//* AptDict_report(&apt_keys);
	
	//* Generate array of pads
	PadArray_fill( &pads, f_sanitised, MULTI_LAYER);
	PadArray_sort( &pads );
	//*PadArray_report( &pads );

	//* Generate array of tracks for BOTTOM_LAYER
	TrackArray_fill( &tracks, f_sanitised, BOTTOM_LAYER);
	TrackArray_sort( &tracks );
	//*TrackArray_report( &tracks );
	
	ArcArray_fill( &arcs, f_sanitised, TOP_OVERLAY);
	ArcArray_sort( &arcs );
	//*ArcArray_report( &arcs );

	FillArray_fill( &fills, f_sanitised, TOP_OVERLAY);
	FillArray_sort( &fills );
	//*FillArray_report( &fills );

	StrArray_fill( &strs, f_sanitised, TOP_OVERLAY);
	StrArray_sort( &strs );
	//*StrArray_report( &strs );

	priminfo.primlist = &pads;
	priminfo.keylist = &apt_keys;
	priminfo.dg_size = 20;

	Wirte2File_Date_Stamp( f_destination );

	//* Header	
	Wirte2File_Units_Inch( f_destination );
	Wirte2File_Format_Info ( f_destination );
	Wirte2File_Image_Neg ( f_destination );
	
	//* Aperture dictionary
	Gerber2File_Apt_Dict( &priminfo, f_destination);
	Gerber2File_Apt_Dict_Pour_Clearance( &priminfo, f_destination);
	
	Wirte2File_Layer_Dark( f_destination);
	priminfo.primlist = &pads;
	Gerber2File_OpCode_pad_clearance (&priminfo, f_destination);
	priminfo.primlist = &tracks;
	Gerber2File_OpCode_track_clearance (&priminfo, f_destination);
	
	Wirte2File_Layer_Clear(f_destination); 
	priminfo.primlist = &pads;
	Gerber2File_OpCode_pad (&priminfo, f_destination);
	priminfo.primlist = &tracks;
	Gerber2File_OpCode_track (&priminfo, f_destination);
	
	
	//* Drill guides
	Wirte2File_Layer_Dark( f_destination);
	priminfo.primlist = &pads;
	Gerber2File_OpCode_dgd (&priminfo, f_destination); 
	
	//* End of file marker
	Wirte2File_M02_EOF (f_destination);
	
	psinfo.primlist = &tracks;
	psinfo.dg_size = 20;
	psinfo.clearance = 20;

	PS2File_header ( f_psfile );
	PS2File_creator ( f_psfile );
	PS2File_date ( f_psfile );
	PS2File_title ( f_psfile, "TEST");
	PS2File_procs ( f_psfile );
	PS2File_translate ( f_psfile, 0.500, 0.500);
	PS2File_scale ( f_psfile, 1, 1);
	PS2File_linecap ( f_psfile ,1);

	psinfo.primlist = &tracks;
	PS2File_trk_dark ( &psinfo, f_psfile, true);
	psinfo.primlist = &pads;
	PS2File_pad_dark ( &psinfo, f_psfile, true);

	psinfo.primlist = &tracks;
	PS2File_trk_clear ( &psinfo, f_psfile, false);
	psinfo.primlist = &pads;
	PS2File_pad_clear ( &psinfo, f_psfile, false);
	PS2File_dgd ( &psinfo, f_psfile, false);
		
	KeyArray_free( &apt_keys);
	PadArray_free( &pads);
	TrackArray_free( &tracks);
	
	fclose(f_source);
	fclose(f_destination);
	fclose(f_sanitised);
	

	return 0;
}

//* START FUNCTIONS

/**
  * PCB_show_version
  *
  * Display the current convgerber version
  */
int PCB_show_version( struct PCB_glb *glb ) {
	fprintf(stderr,"%s\n", PCB_VERSION);
	return 0;
} //* END_FUNC: PCB_show_version

/**
  * PCB_show_help
  *
  * Display the help data for this program
  */
int PCB_show_help( struct PCB_glb *glb ) {
	PCB_show_version(glb);
	fprintf(stderr,"%s\n",HELP_MSG);

	return 0;
} //* END_FUNC: PCB_show_help

/**
  * PCB_parse_cmdline_parameters
  *
  * Parses the command line parameters and sets the
  * various convgerber settings accordingly
  */
int PCB_parse_cmdline_parameters( int argc, char **argv, struct PCB_glb *glb )
{

	char c;

	do {
		c = getopt(argc, argv, "i:o:vh");
		switch (c) { 
			case EOF: /* finished */
				break;

			case 'i':
				glb->src_filename = strdup(optarg);
				break;

			case 'o':
				glb->dest_filename = strdup(optarg);
				break;
			

			case 'h':
				PCB_show_help(glb);
				exit(1);
				break;

			case 'v':
				PCB_show_version(glb);
				exit(1);
				break;

			case '?':
				break;

			default:
				fprintf(stderr, "internal error with getopt\n");
				exit(1);
				
		} //* END: switch (c) 
	} while (c != EOF); /* do */
	return 0;
} //* END_FUNC: PCB_parse_cmdline_parameters


                  

/**
  * PCB_init_global
  *
  * Initializes any variables or such as required by
  * the program.
  */
int PCB_init_global( struct PCB_glb *dest )
{
	dest->status = 0;
	dest->src_filename = NULL;
	dest->dest_filename = NULL;
	dest->temp_filename = "pcbread.tmp";
	return 0;
} //* END_FUNC: PCB_init_global



/**
  * PCB_init_board_info
  *
  * Initializes any variables or such as required by
  * the program.
  */
int PCB_init_board_info( struct PCB_brd_info * dest )
{
	dest->min_x = 0;
	dest->min_x = 0;
	dest->max_x = 0;
	dest->max_y = 0;
	
	dest->board_x = 0;
	dest->board_y = 0;
	
	dest->comp_total = 0;
	
	dest->arc_total = 0;
	dest->comp_arcs = 0;
	dest->free_arcs = 0;

	dest->fill_total = 0;
	dest->comp_fills = 0;
	dest->free_fills = 0;


	dest->pad_total = 0;
	dest->comp_pads = 0;
	dest->free_pads = 0;

	dest->string_total = 0;
	dest->comp_strings = 0;
	dest->free_strings = 0;
	
	dest->track_total = 0;
	dest->comp_tracks = 0;
	dest->free_tracks = 0;
	
	dest->via_total = 0;
	dest->comp_vias = 0;
	dest->free_vias = 0;
	
	return 0;
} //* END_FUNC: PCB_init_board_info




/**
 * PCB_sanitise_src
 * remove all whitespace except NL & SPACE from file
 * when done file pointer is reset to start
 * 
 */
 int PCB_sanitise_src( FILE* f_src, FILE* f_dest)
 {
				int char_read;
	 
	 			while (  ( char_read= fgetc(f_src) ) != EOF ) {	
			
					switch (char_read) {
					
					case ACSII_BS:
					case ACSII_HT:
					case ACSII_VT:
					case ACSII_FF:
					case ACSII_CR:
					case ACSII_DEL:
								break;
					
					default:
								fputc( char_read, f_dest);
			} //* END: switch (char_read)
	} //* END: while (  ( char_read= fgetc(f_src) ) != EOF )
		rewind(f_dest);	
	return 0;
} //* END_FUNC: PCB_sanitise_src
/**
 * PCB_validate_src
 * check for valid hearder 'PCB FILE 4\n'
 * check for valid end marker 'ENDPCB\n'
 * '\n' has been included as we dont want any other characters on 
 * the line of the header & end marker
 */
int PCB_validate_src (FILE * f_src)
{
	char start_buffer[16];
	char end_buffer[16];
	int retn_val;
	
	fgets( start_buffer, 16, f_src);
	fseek(f_src, -7, SEEK_END);
	fgets(end_buffer, 16, f_src);
	fprintf(stderr,"Header is %s", start_buffer);
	fprintf(stderr,"End of file is %s", end_buffer);
	
	if ( (strcmp(start_buffer, PCB_HEADER) == 0 ) && ( strcmp(end_buffer, PCB_END) == 0 )  ) {
		fprintf(stderr,"Valid File\n");
		retn_val = true;
	}
	
	else{
		fprintf(stderr,"Invalid File\n");
		retn_val = false;
	}
   
   rewind (f_src);
   return retn_val;
}



/**
 * PCB_collect_board_information
 * Counts the following primitives
 * Arcs (a)
 * Fills (f)
 * Pad (p)
 * Strings (s)
 * Tracks (t)
 * Vias (v)
 * 
 * for both
 * Components primitives (C)
 * Free primitives (F)
 * 
 * And finally
 * Componets (comps)
 * 
 * 04-12-2016
 * need code to find x_mix, y_min, x_max, y_max 
 */
int PCB_collect_board_information (FILE *f_src, struct PCB_brd_info *src, struct KeyArray_array *apt_keys ) {
	
	int Ca = 0;
	int Fa = 0;
	int Cf = 0;
	int Ff = 0;
	int Cp = 0;
	int Fp = 0;
	int Cs = 0;
	int Fs = 0;
	int Ct = 0;
	int Ft = 0;
	int Cv = 0;
	int Fv = 0;
	struct Primitive_arc_data arc_dat;
	struct Primitive_pad_data pad_dat;
	struct Primitive_string_data string_dat;
	struct Primitive_track_data track_dat;
	struct Primitive_via_data via_dat;
		
	int comps = 0;
	
	char brd_data[64];
		
	uint32_t curr_key = 0;
	uint32_t prev_key = 0;
	
	src->max_x = PCB_MIN_X;
	src->max_y = PCB_MIN_Y;

	src->min_x = PCB_MAX_X;
	src->min_y = PCB_MAX_Y;
	
	
	
		while ( fgets(brd_data, 64, f_src) != NULL ) {
			
			if ( strcmp(brd_data, COMP_ARC) == 0 ) {
				Ca++;
				fgets(brd_data, 64, f_src);
				Primitive_parse_arc( brd_data, &arc_dat);
				XYExntents_arc(src, &arc_dat);
				curr_key = EncodeKey_arc(&arc_dat);
				if ( curr_key != prev_key ) {
					//* fprintf(stderr, "Comp Arc key = %d\n",curr_key);
					KeyArray_insert_key_unique(apt_keys, curr_key);
					prev_key=curr_key;

				}

			}
			if ( strcmp(brd_data, FREE_ARC) == 0 ) {
				Fa++;
				fgets(brd_data, 64, f_src);
				Primitive_parse_arc( brd_data, &arc_dat);
				XYExntents_arc(src, &arc_dat);
				curr_key = EncodeKey_arc(&arc_dat);
				if ( curr_key != prev_key ) {
					//* fprintf(stderr, "Free Arc key = %d\n",curr_key);
					KeyArray_insert_key_unique(apt_keys, curr_key);
					prev_key=curr_key;

				}
			}

			if ( strcmp(brd_data, COMP_FILL) == 0 ) {
				Cf++;
			}
			if ( strcmp(brd_data, FREE_FILL) == 0 ) {
				Ff++;

			}
			
			if ( strcmp(brd_data, COMP_PAD) == 0 ) {
				Cp++;
				fgets(brd_data, 64, f_src);
				Primitive_parse_pad( brd_data, &pad_dat);
				XYExntents_pad(src, &pad_dat);
				curr_key = EncodeKey_pad(&pad_dat);
				if ( curr_key != prev_key ) {
					//* fprintf(stderr, "Comp Pad key = %d\n",curr_key);
					KeyArray_insert_key_unique(apt_keys, curr_key);
					prev_key=curr_key;

				}
			}	

			if ( strcmp(brd_data, FREE_PAD) == 0 ) {
				Fp++;
				fgets(brd_data, 64, f_src);
				Primitive_parse_pad( brd_data, &pad_dat);
				XYExntents_pad(src, &pad_dat);
				curr_key = EncodeKey_pad(&pad_dat);
				if ( curr_key != prev_key ) {
					//* fprintf(stderr, "Free Pad key = %d\n",curr_key);
					KeyArray_insert_key_unique(apt_keys, curr_key);
					prev_key=curr_key;

				}
			}

			if ( strcmp(brd_data, COMP_STRING) == 0 ) {
				Cs++;
				fgets(brd_data, 64, f_src);
				Primitive_parse_string( brd_data, &string_dat);
				curr_key = EncodeKey_string(&string_dat);
				if ( curr_key != prev_key ) {
					//* fprintf(stderr, "Comp String key = %d\n",curr_key);
					KeyArray_insert_key_unique(apt_keys, curr_key);
					prev_key=curr_key;

				}
			}

			if ( strcmp(brd_data, FREE_STRING) == 0 ) {
				Fs++;
				fgets(brd_data, 64, f_src);
				Primitive_parse_string( brd_data, &string_dat);
				curr_key = EncodeKey_string(&string_dat);
				if ( curr_key != prev_key ) {
					//* fprintf(stderr, "Free String key = %d\n",curr_key);
					KeyArray_insert_key_unique(apt_keys, curr_key);
					prev_key=curr_key;

				}
			}
			
			if ( strcmp(brd_data, COMP_TRACK) == 0 ) {
				Ct++;
				fgets(brd_data, 64, f_src);
				Primitive_parse_track( brd_data, &track_dat);
				XYExntents_track(src, &track_dat);
				curr_key = EncodeKey_track(&track_dat);
				if ( curr_key != prev_key ) {
					//* fprintf(stderr, "Comp Track key = %d\n",curr_key);
					KeyArray_insert_key_unique(apt_keys, curr_key);
					prev_key=curr_key;

				}
			}

			if ( strcmp(brd_data, FREE_TRACK) == 0 ) {
				Ft++;
				fgets(brd_data, 64, f_src);
				Primitive_parse_track( brd_data, &track_dat);
				XYExntents_track(src, &track_dat);
				curr_key = EncodeKey_track(&track_dat);
				if ( curr_key != prev_key ) {
					//* fprintf(stderr, "Free Track key = %d\n",curr_key);
					KeyArray_insert_key_unique(apt_keys, curr_key);
					prev_key=curr_key;

				}
			}
			
			if ( strcmp(brd_data, COMP_VIA) == 0 ) {
				Cv++;
				fgets(brd_data, 64, f_src);
				Primitive_parse_via( brd_data, &via_dat);
				XYExntents_via(src, &via_dat);
				curr_key = EncodeKey_via(&via_dat);
				if ( curr_key != prev_key ) {
					//* fprintf(stderr, "Comp Via key = %d\n",curr_key);
					KeyArray_insert_key_unique(apt_keys, curr_key);
					prev_key=curr_key;

				}
			}
				
			if ( strcmp(brd_data, FREE_VIA) == 0 ) {
				Fv++;
				fgets(brd_data, 64, f_src);
				Primitive_parse_via( brd_data, &via_dat);
				XYExntents_via(src, &via_dat);
				curr_key = EncodeKey_via(&via_dat);
				if ( curr_key != prev_key ) {
					//* fprintf(stderr, "Free Via key = %d\n",curr_key);
					KeyArray_insert_key_unique(apt_keys, curr_key);
					prev_key=curr_key;

				}
			}	
			
			if ( strcmp(brd_data, COMP_START) == 0 ) {
				comps++;
			}
						
 				
	} //* END: while ( fgets(brd_data, 64, f_src) != NULL )
	
	src-> board_x = ( src->max_x - src->min_x);
	src-> board_y = ( src->max_y - src->min_y);

	src->comp_total = comps;
	
	src->arc_total = ( Ca + Fa);
	src->comp_arcs = Ca;
	src->free_arcs = Fa;
	
	src->fill_total = ( Cf + Ff );
	src->comp_fills = Cf;
	src->free_fills = Ff;
	
	src->pad_total = ( Cp + Fp );
	src->comp_pads = Cp;
	src->free_pads = Fp;

	src->string_total = ( Cs + Fs );
	src->comp_strings = Cs;
	src->free_strings = Fs; 
	
	src->track_total = ( Ct + Ft);
	src->comp_tracks = Ct;
	src->free_tracks = Ft;
	
	src->via_total = (Cv + Fv);
	src->comp_vias = Cv;
	src->free_vias = Fv;

	rewind(f_src);	
	return 0;
} //* END_FUNC: 

/**
 * PCB_print_brd_info
 * Print information about a board
 * Used during development not for release
 */
int PCB_report_brd_info (struct PCB_brd_info *src ) {
	fprintf(stderr, "Component Arcs: %i\tFree Arcs: %i\tTotal Arcs: %i\n", src->comp_arcs, src->free_arcs, src->arc_total);	
	fprintf(stderr, "Component Fills: %i\tFree Fills: %i\tTotal Fills: %i\n", src->comp_fills, src->free_fills, src->fill_total);	
	fprintf(stderr, "Component Pads: %i\tFree Pads: %i\tTotal Pads: %i\n", src->comp_pads, src->free_pads, src->pad_total);
	fprintf(stderr, "Component Strings: %i\tFree Strings: %i\tTotal Strings: %i\n", src->comp_strings, src->free_strings, src->string_total);
	fprintf(stderr, "Component Tracks: %i\tFree Tracks: %i\tTotal Tracks: %i\n", src->comp_tracks, src->free_tracks, src->track_total);
	fprintf(stderr, "Component Vias: %i\tFree Vias: %i\tTotal Vias: %i\n", src->comp_vias, src->free_vias, src->via_total);
	fprintf(stderr, "Total Components: %i\n", src->comp_total);	
	fprintf(stderr, "Board size: %d x %d\n", src->board_x, src->board_y);
	fprintf(stderr, "Min X: %5d\tMin Y: %5d\n", src->min_x, src->min_y);
	fprintf(stderr, "Max X: %5d\tMax Y: %5d\n\n", src->max_x, src->max_y);
	
	
	
return 0;
} //* END_FUNC: PCB_print_board_info


