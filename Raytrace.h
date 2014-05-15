#ifndef CSE168_RAYTRACE_H
#define CSE168_RAYTRACE_H

#include "Intersection.h"
#include "Material.h"
#include "Ray.h"
#include "Scene.h"
#include "Color.h"

#define MAX_DEPTH 10
class Raytrace {
public:
	Raytrace(){}
	~Raytrace(){};
	Color TraceRay(const Ray &ray, Intersection &hit, Scene &s, int depth = 0) {
		if (depth == MAX_DEPTH) {
			return Color::BLACK;
		}
		if (!s.Intersect(ray, hit)) {
			return s.GetSkyColor();
		}
		
		// Sample the new ray
		Color color = Color::BLACK;
		Ray newray;
		if (hit.Mtl != NULL) {
			hit.Mtl->SampleRay(ray, hit, newray, color);
			Intersection tmphit;
			Color tmpcolor = TraceRay(newray, tmphit, s, depth + 1);
			color.Multiply(tmpcolor);
		}

		int numLights = s.GetNumLights();

		for (int i = 0; i < numLights; ++i) {
			Color tmp;
			Vector3 tolight, ltpos;
			
			float intensity = s.GetLight(i).Illuminate(hit.Position, tmp, tolight, ltpos);
			if (hit.Normal.Dot(tolight) < 0) continue;
			if (intensity < (0.5 / 255.0)) continue;

			// shading 
			Ray lightreverse; Intersection shade;
			lightreverse.Direction = tolight;
			lightreverse.Origin = hit.Position;
			shade.HitDistance = (ltpos - hit.Position).Magnitude();
			if (s.Intersect(lightreverse, shade)) continue;

			tmp.Scale(intensity);
			if (hit.Mtl != NULL) {
				Color reflectance; 
				hit.Mtl->ComputeReflectance(reflectance, -ray.Direction, tolight, hit);
				tmp.Multiply(reflectance);
				tmp.Scale((tolight).Dot(hit.Normal));
			}
			else {
				tmp.Scale((tolight).Dot(hit.Normal));
			}
			color.Add(tmp);
		}
		return color;
	}
};

#endif