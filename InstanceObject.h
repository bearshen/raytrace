#ifndef CSE168_INSTANCEOBJECT_H
#define CSE168_INSTANCEOBJECT_H
#include "Object.h"
#include "Matrix34.h"
#include "BoxTreeObject.h"
class InstanceObject : public Object{
public:
	InstanceObject() {
		Mtl = NULL;
	}
	InstanceObject(Object &obj) {
		Mtl = NULL;
		SetChild(obj);
	}
	InstanceObject(Object &obj, Material* mtl) {
		SetChild(obj);
		SetMaterial(mtl);
	}
	bool Intersect(const Ray &ray, Intersection &hit) {
		Ray ray2;
		Inverse.Transform(ray.Origin, ray2.Origin);
		Inverse.Transform3x3(ray.Direction, ray2.Direction);
		if (Child->Intersect(ray2, hit) == false) return false;
		Matrix.Transform(hit.Position, hit.Position);
		Matrix.Transform3x3(hit.Normal, hit.Normal);
		hit.HitDistance = ray.Origin.Distance(hit.Position); // Correct for any scaling 
		if (Mtl != NULL) {
			hit.Mtl = Mtl;
		}
		return true;
	}
	void SetChild(Object &obj) {
		Child = &obj;
	}
	void SetMaterial(Material *mtl) {
		Mtl = mtl;
	}
	void SetMatrix(const Matrix34 &mtx) {
		Matrix = mtx;
		Inverse = mtx;
		Inverse.Inverse();
	}

private:
	Matrix34 Matrix;
	Matrix34 Inverse; // Pre-computed inverse of Matrix 
	Object *Child;
	Material* Mtl;
};
#endif 