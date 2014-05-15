#include "AshikhminMaterial.h"
#include "Ray.h"
#include <cmath>
using std::fmin;
using std::sqrt;
using std::pow;

float clamp(float f) {
	if (f < 0.0f)
		f = 0.0f;
	if (f > 1.0f)
		f = 1.0f;
	return f;
}

void AshikhminMaterial::SetDiffuseColor(Color &color) {
	DiffuseColor = color;
}
void AshikhminMaterial::SetDiffuseLevel(float level) {
	DiffuseLevel = level;
}
void AshikhminMaterial::SetRoughness(float u, float v) {
	RoughnessU = u;
	RoughnessV = v;
}
void AshikhminMaterial::SetSpecularColor(Color &color){
	SpecularColor = color;
}
void AshikhminMaterial::SetSpecularLevel(float level){
	SpecularLevel = level;
}
void AshikhminMaterial::ComputeReflectance(Color &col, const Vector3 &in, const Vector3 &out, const Intersection &hit) {
	// calculate BRDF constants, according to 
	// http://www.cs.utah.edu/~michael/brdfs/jgtbrdf.pdf
	col = Color::BLACK;
	float s = SpecularLevel;
	float d = DiffuseLevel;
	// Specular and Diffuse Components
	float Rs, Rd; // R stands for rou

	Vector3 k1 = in;
	Vector3 k2 = out;
	float ru = RoughnessU;
	float rv = RoughnessV;
	Vector3 hu = hit.TangentU;
	Vector3 hv = hit.TangentV;
	Vector3 n = hit.Normal;
	
	Vector3 h = (in + out);
	h.Normalize();

	float kh = out.Dot(h);
	float nh = hit.Normal.Dot(h);

	float nk1 = k1.Dot(n);
	float nk2 = k2.Dot(n);
	if (nk2 < 0) {
		return;
	}
	float hhu = h.Dot(hu);
	float hhv = h.Dot(hv);

	float F = s + (1.0f - s) * pow(1.0f - kh, 5.0f);

	float Ps1 = sqrt((ru + 1) * (rv + 1)) / (8.0f * PI);
	float Ps2 = pow(nh, ((ru * hhu * hhu + rv * hhv * hhv) / (1.0f - nh * nh))) / (kh * fmax(nk1, nk2));
	Rs = Ps1 * Ps2 * F;

	float Rd1 = ((28.0f * d) / (23.0f * PI)) * (1.0f - s);
	float Rd2 = 1.0f - pow(1.0f - 0.5f * nk1, 5.0f);
	float Rd3 = 1.0f - pow(1.0f - 0.5f * nk2, 5.0f);
	Rd = Rd1 * Rd2 * Rd3;
	
	col.AddScaled(SpecularColor, Rs);
	col.AddScaled(DiffuseColor, Rd);
}

void AshikhminMaterial::SampleRay(const Ray &ray, const Intersection &hit, Ray &newRay, Color &color)
{
	if (float(rand()) / RAND_MAX < SpecularLevel) {
		float E_1 = float(rand()) / RAND_MAX;
		float E_2 = float(rand()) / RAND_MAX;
		float phi = atan(sqrt((RoughnessU + 1.0f) / (RoughnessV + 1.0f)) * tan(PI * E_1 * 0.5f));
		float quadrant = float(rand()) / RAND_MAX;

		if (quadrant > 0.75f) {
			phi = 2.0f * PI - phi;
		}
		else if (quadrant > 0.5f) {
			phi = PI + phi;
		}
		else if (quadrant > 0.25f) {
			phi = PI - phi;
		}
		float cos_theta = pow(1.0f - E_2, 1.0f / (RoughnessU * pow(cos(phi), 2.0f) + RoughnessV * pow(sin(phi), 2.0f) + 1.0f));
		float sin_theta = sin(acos(cos_theta));
		Vector3 h = hit.Normal * cos_theta + hit.TangentU * sin_theta * cos(phi) + hit.TangentV * sin_theta * sin(phi);
		h.Normalize();
		Vector3 k1 = -ray.Direction;
		Vector3 k2 = -k1 + 2.0f * k1.Dot(h) * h; 
		if (k2.Dot(hit.Normal) < 0.0f) {
			color = Color::BLACK;
			return;
		}
		k2.Normalize();

		newRay.Origin = hit.Position;
		newRay.Direction = k2;
		color = SpecularColor;
	}
	else {
		float s = float(rand()) / RAND_MAX;
		float t = float(rand()) / RAND_MAX;
		float u = 2.0f * PI * s;
		float v = sqrt(1.0f - t);

		newRay.Origin = hit.Position;
		newRay.Direction = hit.Normal * sqrt(t) + hit.TangentU * v * cos(u) + hit.TangentV * v * sin(u);
		newRay.Direction.Normalize();
		color = DiffuseColor;
	}
}