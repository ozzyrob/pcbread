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
#include <stdio.h>
#include <string.h>
#include "pcb.h"
#include "primitive.h"

#ifndef XYEXTENTS_H
#define XYEXTENTS_H

int XYExntents_arc ( struct PCB_brd_info * brd, struct Primitive_arc_data * arc);
int XYExntents_fill ( struct PCB_brd_info * brd, struct Primitive_fill_data * fill);
int XYExntents_pad ( struct PCB_brd_info * brd, struct Primitive_pad_data * pad);
int XYExntents_string ( struct PCB_brd_info * brd, struct Primitive_string_data * str);
int XYExntents_track ( struct PCB_brd_info * brd, struct Primitive_track_data * trk);
int XYExntents_via ( struct PCB_brd_info * brd, struct Primitive_via_data * via);

#endif //* XYENTENTS_H
