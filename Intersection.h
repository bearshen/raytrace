#ifndef CSE168_INTERSECTION_H
#define CSE168_INTERSECTION_H

#include "Vector3.h"
#include "Color.h"

class Material;

////////////////////////////////////////////////////////////////////////////////

class Intersection {
public:
	Intersection() { HitDistance = 1e10; Mtl = NULL; };
	// Ray intersection data
	Material *Mtl;
	float HitDistance;
	Vector3 Position;
	Vector3 Normal;
	Vector3 TangentU;
	Vector3 TangentV;
	// Shaded color
	Color Shade;
};

////////////////////////////////////////////////////////////////////////////////

#endif
