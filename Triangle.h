////////////////////////////////////////
// Triangle.h
////////////////////////////////////////

#ifndef CSE168_TRIANGLE_H
#define CSE168_TRIANGLE_H

#include "Vertex.h"
#include "Material.h"
#include "Ray.h"

////////////////////////////////////////////////////////////////////////////////

class Triangle {
public:
	Triangle() {};
	void Init(Vertex *v0,Vertex *v1,Vertex *v2,Material *m)		{Vtx[0]=v0; Vtx[1]=v1; Vtx[2]=v2; Mtl=m;}

	bool Intersect(const Ray &ray, Intersection &hit);
	Vertex& GetVtx(int i) {
		return *Vtx[i];
	}
private:
	Vertex *Vtx[3];
	Material *Mtl;
};

////////////////////////////////////////////////////////////////////////////////

#endif
