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

