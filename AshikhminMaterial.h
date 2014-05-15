#ifndef ASHIKHMINMATERIAL_H
#define ASHIKHMINMATERIAL_H
#include "Material.h"
#include "Color.h"
class AshikhminMaterial : public Material {
public:
	AshikhminMaterial(){
		SpecularLevel = 1.0;
		DiffuseColor = Color::WHITE;
		SpecularColor = Color::WHITE;
	}
	void SetSpecularLevel(float level);
	void SetDiffuseLevel(float level);
	void SetDiffuseColor(Color &color);
	void SetSpecularColor(Color &color);
	void SetRoughness(float u, float v);
	void ComputeReflectance(Color &col, const Vector3 &in, const Vector3 &out, const Intersection &hit);
	void SampleRay(const Ray &ray, const Intersection &hit, Ray &newRay, Color &intensity);
private:
	float SpecularLevel;
	float DiffuseLevel;
	Color DiffuseColor;
	Color SpecularColor;
	float RoughnessU, RoughnessV;
};

#endif