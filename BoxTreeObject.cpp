#include "BoxTreeObject.h"
#include "MeshObject.h"
#include <Windows.h>
#include <iostream>
using std::endl;
using std::cout;
BoxTreeObject::BoxTreeObject()
{
	RootNode = new BoxTreeNode();
}


BoxTreeObject::~BoxTreeObject()
{
}

void BoxTreeObject::Construct(MeshObject &mesh) {
	Triangle** triangles = mesh.GetTriangles();
	int numTriangles = mesh.GetNumTriangles();
	
	RootNode->Construct(numTriangles, triangles);
	delete[] triangles;
}

bool BoxTreeObject::Intersect(const Ray &ray, Intersection &hit) {
	return RootNode->Intersect(ray, hit);
}