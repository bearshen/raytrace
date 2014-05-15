#include "Triangle.h"
#include "Matrix34.h"
#include "Vector3.h"

float eps = 0.00001f; // tested , 1e-10 is too small. 
bool Triangle::Intersect(const Ray &ray, Intersection &hit) {
	Matrix34 M = Matrix34();
	Vector3 a, b, c ,ab, ac, bc;
	a = GetVtx(0).Position;
	b = GetVtx(1).Position;
	c = GetVtx(2).Position;
	ab = b - a;
	ac = c - a;
	bc = c - b;

	M.a = -ray.Direction;
	M.b = ab;
	M.c = ac;
	Vector3 p = ray.Origin - a;
	Vector3 cross;
	cross.Cross(ab, ac);
	float detM = (-ray.Direction).Dot(cross);
	if (abs(detM) == 0) return false;
	cross.Cross(p, ac);
	float alpha = (-ray.Direction).Dot(cross) / detM;
	if (alpha < 0 || alpha > 1) return false;
	cross.Cross(ab, p);
	float beta = (-ray.Direction).Dot(cross) / detM;
	if (beta < 0 || (alpha + beta > 1)) return false;
	cross.Cross(ab, ac);
	float t = p.Dot(cross) / detM;

	if ((t < eps) || (t >= hit.HitDistance)) return false;

	// true
	Vector3 nA = GetVtx(0).Normal;
	nA.Scale(1 - alpha - beta);
	Vector3 nB = GetVtx(1).Normal;
	nB.Scale(alpha);
	Vector3 nC = GetVtx(2).Normal;
	nC.Scale(beta);
	

	// hit
	hit.HitDistance = t;
	hit.Mtl = Mtl;
	hit.Position = ray.Origin;
	hit.Position.AddScaled(ray.Direction, t);
	hit.Normal = nA + nB + nC;
	hit.Normal.Normalize();
	hit.TangentU.Cross(Vector3::YAXIS, hit.Normal);
	if (hit.TangentU.Magnitude2() == 0)
		hit.TangentU.Cross(Vector3::XAXIS, hit.Normal);
	hit.TangentU.Normalize();
	hit.TangentV.Cross(hit.Normal, hit.TangentU);
	hit.TangentV.Normalize();

	return true;
}
