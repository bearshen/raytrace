////////////////////////////////////////
// MeshObject.h
////////////////////////////////////////

#ifndef CSE168_MESHOBJECT_H
#define CSE168_MESHOBJECT_H

#include "Object.h"
#include "Triangle.h"

////////////////////////////////////////////////////////////////////////////////

class MeshObject:public Object {
public:
	MeshObject();
	~MeshObject();
	bool LoadPLY(const char *filename, Material *mtl);
	void Smooth();
	bool Intersect(const Ray &ray,Intersection &hit);
	Triangle ** GetTriangles() {
		Triangle** triangles;
		triangles = new Triangle*[NumTriangles];
		for (int i = 0; i < NumTriangles; i++) {
			triangles[i] = &Triangles[i];
		}
		return triangles;
	}
	int GetNumTriangles() { return NumTriangles; }
	Vertex ** GetVertexes() { return &Vertexes; }
	int GetNumVertexes() { return NumVertexes; }
	void MakeBox(float x,float y,float z,Material *mtl=0);

private:
	int NumVertexes,NumTriangles;
	Vertex *Vertexes;
	Triangle *Triangles;
};

////////////////////////////////////////////////////////////////////////////////

#endif
