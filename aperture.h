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
