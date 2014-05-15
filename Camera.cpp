#include "Camera.h"
#include "Intersection.h"
#include "Raytrace.h"
#include <cmath>
using std::atan;
using std::tan;
const float inf = 1e10;

void Camera::Render(Scene &s) {
	// Get width FOV.
	float HorizontalFOV = 2 * atan(Aspect * tan(VerticalFOV / 2));
	Vector3 ScaledB = WorldMatrix.b;
	ScaledB.Scale(tan(VerticalFOV / 2));
	Vector3 ScaledA = WorldMatrix.a;
	ScaledA.Scale(tan(HorizontalFOV / 2));

	// get four primary rays
	Vector3 upperleft = WorldMatrix.d - WorldMatrix.c + ScaledB - ScaledA;
	Vector3 upperright = WorldMatrix.d - WorldMatrix.c + ScaledB + ScaledA;
	Vector3 lowerleft = WorldMatrix.d - WorldMatrix.c - ScaledB - ScaledA;
	Vector3 lowerright = WorldMatrix.d - WorldMatrix.c - ScaledB + ScaledA;
	Vector3 hdis = upperright - upperleft;
	float hdelta = hdis.Magnitude() / XRes;
	Vector3 vdis = upperleft - lowerleft;
	float vdelta = vdis.Magnitude() / YRes;
	hdis.Normalize(); vdis.Normalize();
	Ray ray;
	ray.Origin = WorldMatrix.d;
	for (int y = 0; y < YRes; ++y) {
		for (int x = 0; x < XRes; ++x) {
			printf("Printing point (%d, %d)\n", x, y);
			// set the ray direction. 
			ray.Direction = lowerleft;
			ray.Direction.AddScaled(hdis, (x + 0.5) * hdelta);
			ray.Direction.AddScaled(vdis, (y + 0.5) * vdelta);
			ray.Direction = ray.Direction - WorldMatrix.d;
			ray.Direction.Normalize();
			Color aggregatedcolor = Color::BLACK;
			Raytrace r;

			// Supersampling
			#pragma omp parallel for
			for (int i = 0; i < nSamples; ++i)
			#pragma omp parallel for
			for (int j = 0; j < nSamples; ++j) {
				Color pixelcolor = RenderPixel(ray, s);
				aggregatedcolor.Add(pixelcolor);
			}

			aggregatedcolor.Scale(float(1.0f / (float)(nSamples * nSamples)));

			BMP.SetPixel(x, y, aggregatedcolor.ToInt());
		}
	}
}

Color Camera::RenderPixel(Ray &ray, Scene &s) {
	Raytrace tmpraytrace;
	Intersection hit;
	return tmpraytrace.TraceRay(ray, hit, s, 0);
}