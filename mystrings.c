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

//*#include "mystrings.h"

const char * PCB_HEADER = "PCB FILE 4\n";
const char * PCB_END = "ENDPCB\n";
const char * COMP_START = "COMP\n";
const char * COMP_END = "ENDCOMP\n"; 
/**
 * primitive types
 * F = free primitive
 * C = component primitive
 */
const char * FREE_ARC = "FA\n";
const char * FREE_FILL = "FF\n";
const char * FREE_PAD = "FP\n";
const char * FREE_STRING = "FS\n";
const char * FREE_TRACK = "FT\n";
const char * FREE_VIA = "FV\n";
const char * COMP_ARC = "CA\n";
const char * COMP_FILL = "CF\n";
const char * COMP_PAD = "CP\n";
const char * COMP_STRING = "CS\n";
const char * COMP_TRACK = "CT\n";
const char * COMP_VIA = "CV\n";

const char * HELP_MSG = "pcbread: Protel Autotrax gerber generator\n"
	                    "Written by Robert Murphy.\n"
	                    "This software is available at https://github.com/ozzyrob/convgerber\n"
	                    "License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>\n"
	                    "\n"
	                    "This is free software; you are free to change and redistribute it.\n"
	                    "There is NO WARRANTY, to the extent permitted by law.\n"
	                    "\n"
	                    "Usage: pcbread -i <input PCB> -o <output GERBER> [-v] [-h]\n"
	                    "\n"
	                    "\t-i <input PCB> : Specifies Protel Autotrax input file.\n"
	                    "\t-o <output DAT> : Specifies otput file.\n"
	                    "\n"
	                    "\t-v : Display current software version\n"
	                    "\t-h : Display this help.\n"
	                    "\n";
