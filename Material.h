#ifndef CSE168_MATERIAL_H
#define CSE168_MATERIAL_H

#include "Color.h"
#include "Intersection.h"
#include "Vector3.h"
#include "Ray.h"

class Material {
public:
	virtual void ComputeReflectance(Color &col, const Vector3 &in, const Vector3 &out, const Intersection &hit) = 0;
	virtual void SampleRay(const Ray &ray, const Intersection &hit, Ray &newRay, Color &intensity) = 0;
};

#endif
