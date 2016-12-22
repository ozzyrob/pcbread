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

#ifndef HELPMSG_H
#define HELPMSG_H

//* Help Message
const char HELP_MSG[]= "convgerber: FlatCAM cnc file converter\n"
	                    "Written by Robert Murphy.\n"
	                    "This software is available at https://github.com/ozzyrob/convgerber\n"
	                    "License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>\n"
	                    "\n"
	                    "This is free software; you are free to change and redistribute it.\n"
	                    "There is NO WARRANTY, to the extent permitted by law.\n"
	                    "\n"
	                    "Usage: pcbread -i <input CNC> -o <output HPGL> [-p] [-v] [-h]\n"
	                    "\n"
	                    "\t-i <input PCB> : Specifies Protel Autotrax input file.\n"
	                    "\t-o <output DAT> : Specifies otput file.\n"
	                    "\n"
	                    "\t-v : Display current software version\n"
	                    "\t-h : Display this help.\n"
	                    "\n";
#endif /* HELPMSG_H */
