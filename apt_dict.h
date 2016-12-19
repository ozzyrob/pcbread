#include <stdint.h>
#include "key_array.h"

#ifndef APTDICT_H
#define APTDICT_H

/** AptDict_dcode & Apt_Dict_report are generally 
 *  the only functions called externally
 */ 
void AptDict_dcode( struct KeyArray_array * ptr, int dcode );
void AptDict_report( struct KeyArray_array * ptr);
void AptDict_fill( struct KeyArray_array * ptr, int dgd_size ); 

/** These 4 functions are generally just helper functions for
 *  Apt_Dict_dcode
 *  but can be called from outside this file
 */ 
void AptDict_circle( uint32_t key, int dcode, char * apt_def, char * apt_pour, float pour_clr, int offset);
void AptDict_rectangle( uint32_t key, int dcode, char * apt_def, char * apt_pour, float pour_clr, int offset);
void AptDict_obround( uint32_t key, int dcode, char * apt_def, char * apt_pour, float pour_clr, int offset);
void AptDict_regpoly( uint32_t key, int dcode, char * apt_def, char * apt_pour, float pour_clr, int offset);

#endif //* APTDICT_H

