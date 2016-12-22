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
#include "pcb.h"
#include "apt_dict.h"

/** void AptDict_dcode
 *  Calls function based on shape to
 *  fills in an aperture definition 
 *  from a key based on supplied index
 *  struct KeyArray_aperture {
 *  uint32_t key;
 *  char definition[32]; <-------- this field here
 *  };	
 *  08-12-2016:
 *  Moiro & Cross Hair targets not implemented
 */ 
void AptDict_dcode( struct KeyArray_array * ptr, int index ) {

	//* These next 2 lines are just to make code more readable
	//* for myself
	uint32_t src_key = ptr->array[index].key;
	float pour_clr = (float) ptr->pour_clearance/500;
	char * apt_def = ptr->array[index].definition;
	char * apt_pour =  ptr->array[index].pour_def;

	int shape =  ( src_key & 0x07 );
	int dcode = index + 10;
	int pour_dcode = ptr->used + dcode +1;
	
	switch ( shape ) {
	
		case PAD_SHAPE_CIRC:
			AptDict_circle( src_key, dcode, apt_def, apt_pour, pour_clr, pour_dcode);
			break;

		case PAD_SHAPE_DGD:
			AptDict_circle( src_key, dcode, apt_def, apt_pour, pour_clr, pour_dcode);
			break;
	
		case PAD_SHAPE_RECT:
			AptDict_rectangle( src_key, dcode, apt_def, apt_pour, pour_clr, pour_dcode);
			break;
			
		case PAD_SHAPE_OCT:
			AptDict_regpoly( src_key, dcode, apt_def, apt_pour, pour_clr, pour_dcode);
			break;
			
		case PAD_SHAPE_RND_RECT:
			AptDict_obround( src_key, dcode, apt_def, apt_pour, pour_clr, pour_dcode);
			break;
			
		default:
			fprintf(stderr, "Invalid shape\n");
		}
			
	return;
}
/** AptDict_circle
 *  hole diameter is not used
 *  C,<Diameter>[X<Hole diameter>]
 */ 
void AptDict_circle( uint32_t src_key, int dcode, char * apt_def, char * apt_pour, float pour_clr, int pour_dcode) {
	
	float diameter = (float) ( ( src_key >> 13) & 0x03FF ) / 1000;
	//* fprintf(stderr, "Aperture\n%d %d %%ADD%dC,%2.3f*%%\n", dcode, src_key, dcode, diameter);
	sprintf(apt_def, "%%ADD%dC,%2.3f*%%", dcode, diameter);
	if ( pour_clr != 0 ) {
		sprintf(apt_pour, "%%ADD%dC,%2.3f*%%", pour_dcode, diameter + pour_clr);
	}
	return;
}
/** AptDict_rectangle
 *  hole diameter is not used
 *  R,<X size>X<Y size>[X<Hole diameter>]
 */
void AptDict_rectangle( uint32_t src_key, int dcode, char * apt_def, char * apt_pour, float pour_clr, int pour_dcode) {
	
	float x_size = (float) ( ( src_key >> 13) & 0x03FF ) / 1000;
	float y_size = (float) ( ( src_key >> 3 ) & 0x03FF ) / 1000;
	//* fprintf(stderr, "Aperture\n%d %d %%ADD%dR,%2.3fX%2.3f*%%\n", dcode, src_key, dcode, x_size, y_size);
	sprintf(apt_def, "%%ADD%dR,%2.3fX%2.3f*%%", dcode, x_size, y_size);
	if ( pour_clr != 0 ) {
		sprintf(apt_pour, "%%ADD%dR,%2.3fX%2.3f*%%", pour_dcode, x_size + pour_clr, y_size + pour_clr);
	}
	return;
}

/** AptDict_obround
 *  hole diameter is not used
 *  O,<X size>X<Y size>[X<Hole diameter>]
 */
void AptDict_obround( uint32_t src_key, int dcode, char * apt_def, char * apt_pour, float pour_clr, int pour_dcode) {

	float x_size = (float) ( ( src_key >> 13) & 0x03FF ) / 1000;
	float y_size = (float) ( ( src_key >> 3 ) & 0x03FF ) / 1000;
	//* fprintf(stderr, "Aperture\n%d %d %%ADD%dO,%2.3fX%2.3f*%%\n", dcode, src_key, dcode, x_size, y_size);
	sprintf(apt_def, "%%ADD%dO,%2.3fX%2.3f*%%", dcode, x_size, y_size);
	if ( pour_clr != 0 ) {
		sprintf(apt_pour, "%%ADD%dO,%2.3fX%2.3f*%%", pour_dcode, x_size + pour_clr, y_size + pour_clr);
	}
	return;
}

/** AptDict_regpoly
 *  hole diameter is not used
 *  P,<Outer diameter>X<Number of vertices>[X<Rotation>[X<Hole diameter>]]
 */
void AptDict_regpoly( uint32_t src_key, int dcode, char * apt_def, char * apt_pour, float pour_clr, int pour_dcode) {
	
	float diameter = (float) ( ( src_key >> 13) & 0x03FF ) / 1000;
	int vertices = 8;
	float rotation = 22.5;

	//* fprintf(stderr, "Aperture\n%d %d %%ADD%dP,%2.3fX%dX%2.3f*%%\n", dcode, src_key, dcode, diameter, vertices, rotation);
	sprintf(apt_def, "%%ADD%dP,%2.3fX%dX%2.3f*%%", dcode, diameter, vertices, rotation);
	if ( pour_clr != 0 ) {
		sprintf(apt_pour, "%%ADD%dP,%2.3fX%dX%2.3f*%%", pour_dcode, diameter + pour_clr, vertices, rotation);
	}
	return;
}

/** AptDict_report
 * Print the following to stderr
 * Aperture No:
 * Key:
 * String:
 */ 

void AptDict_report( struct KeyArray_array * ptr) {
	
	int index = 0;
	
	fprintf(stderr,"\n**** Aperture List ****\n");
	
	for ( index=0; index < ptr->used; index++ ) {
		fprintf(stderr,"Aperture No: %d\nKey: %d\nString: %s\n", index+10, ptr->array[index].key, ptr->array[index].definition);
		fprintf(stderr,"Clearnce String: %s\n\n", ptr->array[index].pour_def);
	}
}

/** void AptDict_fill
 *  Fill in definition field for all array members
 *  struct KeyArray_aperture {
 *  uint32_t key;
 *  *char definition[32]; <-------- this field here
 *  };
 *  Add key & definition for Drill Guide
 */	
void AptDict_fill( struct KeyArray_array * ptr, int dgd_size ) {
	
	int index = 0;
	uint32_t drill_guide = ( ( dgd_size << 13 ) | ( dgd_size << 3 ) | PAD_SHAPE_DGD );
	int list_size = ptr->used;
	int saved_pour_clearance = ptr->pour_clearance;
		
	for ( index=0; index < list_size; index++ ) {
		AptDict_dcode( ptr, index);
	}
	
	KeyArray_insert_key( ptr, drill_guide);
	ptr->pour_clearance = 0;
	AptDict_dcode( ptr,index);
	ptr->pour_clearance = saved_pour_clearance;
}
