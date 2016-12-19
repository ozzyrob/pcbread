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
