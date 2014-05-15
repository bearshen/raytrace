////////////////////////////////////////
// LambertMaterial.h
////////////////////////////////////////

#ifndef CSE168_LAMBERTMATERIAL_H
#define CSE168_LAMBERTMATERIAL_H
#include <cstdlib>
#include <cmath>
using std::sqrt;
using std::cos;
using std::sin;
using std::rand;
#include "Material.h"

////////////////////////////////////////////////////////////////////////////////

class LambertMaterial:public Material {
public:
	void ComputeReflectance(Color &col, const Vector3 &in, const Vector3 &out, const Intersection &hit) {
		col = DiffuseColor;
		col.Scale(hit.Normal.Dot(out));
	}
	void SampleRay(const Ray &ray, const Intersection &hit, Ray &newRay, Color &color) {
		float s = float(rand()) / RAND_MAX;
		float t = float(rand()) / RAND_MAX;
		float u = 2.0f * PI * s;
		float v = sqrt(1.0f - t);

		newRay.Origin = hit.Position;
		newRay.Direction = hit.Normal * sqrt(t) + hit.TangentU * v * cos(u) + hit.TangentV * v * sin(u);
		color = DiffuseColor;
	}
	void SetDiffuseColor(Color color) {
		DiffuseColor = color;
	}
private:
	Color DiffuseColor;
};

////////////////////////////////////////////////////////////////////////////////

#endif
