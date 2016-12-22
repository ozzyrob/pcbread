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

#ifndef APERTURE_H
#define APERTURE_H
/**
 * C,<Diameter>[X<Hole diameter>]
 */ 
struct APT_Circle {
	int dcode;
	char *apt_name;
	int diameter;
	int hole_size;
};

/**
 * R,<X size>X<Y size>[X<Hole diameter>]
 */ 
struct APT_Rectangle {
	int dcode;
	char *apt_name;
	int x_size;
	int y_size;
	int hole_size;
};

/**
 * O,<X size>X<Y size>[X<Hole diameter>]
 */
struct APT_Obround {
	int dcode;
	char *apt_name;
	int x_size;
	int y_size;
	int hole_size;
};

/**
 * P,<Outer diameter>X<Number of vertices>[X<Rotation>[X<Hole diameter>]]
 */
struct   APT_Poly {
	int dcode;
	char *apt_name;
	int diameter;
	int num_vertices;
	int rotation;
	int hole_size;
};
/** 
 * Holder for decoded key
 */ 
struct APT_raw {
	int x_size;
	int y_size;
	int shape;
};
#endif /* APERTURE_H */
