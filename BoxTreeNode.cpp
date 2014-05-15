#include "BoxTreeNode.h" // defined MAX_TRIANGLES_PER_BOX
#include <cmath>
#include <cassert>
#include <iostream>
using std::cout;
using std::endl;
using std::fmax;
using std::fmin;
const float inf = 1e10; // infinity
const float minf = -1e10; // minus infinity

bool BoxTreeNode::Intersect(const Ray &ray, Intersection &hit) {
	bool hit1 = false, hit2 = false;
	bool boxhit = false;
	// AABB test
	float t, t1[3], t2[3], tmin, tmax;
	for (int i = 0; i < 3; ++i) {
		t1[i] = ((BoxMin[i] - ray.Origin[i]) / ray.Direction[i]);
		t2[i] = ((BoxMax[i] - ray.Origin[i]) / ray.Direction[i]);
	}
	tmin = Max(Max(Min(t1[0], t2[0]), Min(t1[1], t2[1])), Min(t1[2], t2[2]));
	tmax = Min(Min(Max(t1[0], t2[0]), Max(t1[1], t2[1])), Max(t1[2], t2[2]));

	if (tmin <= tmax) {
		boxhit = true;
	}
	else if (ray.Origin[0] >= BoxMin[0] && ray.Origin[0] <= BoxMax[0]
		&& ray.Origin[1] >= BoxMin[1] && ray.Origin[1] <= BoxMax[1]
		&& ray.Origin[2] >= BoxMin[2] && ray.Origin[2] <= BoxMax[2])
		boxhit = true;

	// test if it is leaf
	if (boxhit && NumTriangles != 0) {

		assert(NumTriangles <= MAX_TRIANGLES_PER_BOX);
		bool success = false;
		for (int i = 0; i < NumTriangles; ++i) {
			if (Tri[i]->Intersect(ray, hit)) {
				success = true;
			}
		}
		return success;
	}
	// test two childs.
	if (boxhit && Child1 != NULL) {
		hit1 = Child1->Intersect(ray, hit);
	}
	if (boxhit && Child2 != NULL) {
		hit2 = Child2->Intersect(ray, hit);
	}
	return (hit1 || hit2);
}

void BoxTreeNode::Construct(int count, Triangle ** tri) {
	assert(count != 0);
	BoxMin = Vector3{ inf, inf, inf };
	BoxMax = Vector3{ minf, minf, minf };
	for (int i = 0; i < count; ++i) {
		for (int j = 0; j < 3; ++j) {
			for (int k = 0; k < 3; ++k) {
				BoxMin[k] = fmin(BoxMin[k], tri[i]->GetVtx(j).Position[k]);
				BoxMax[k] = fmax(BoxMax[k], tri[i]->GetVtx(j).Position[k]);
			}
		}
	}
	if (count <= MAX_TRIANGLES_PER_BOX) {
		Child1 = Child2 = NULL;
		for (int i = 0; i < count; ++i) {
			Tri[i] = new Triangle();
			*Tri[i] = *tri[i];
		}
		NumTriangles = count;
		return;
	}
	else {
		NumTriangles = 0;
		// get the largest dimension, and split that. 
		int splitdim = 0;
		float maxsplit = BoxMax[splitdim] - BoxMin[splitdim];
		for (int i = 1; i < 3; ++i) {
			float split = BoxMax[i] - BoxMin[i];
			if (maxsplit < split) {
				maxsplit = split;
				splitdim = i;
			}
		}

		float splitpoint = (BoxMax[splitdim] + BoxMin[splitdim]) / 2;

		int count1 = 0;
		int j = 0;
		for (int i = 0, k = count-1; i < count; ++i) {
			float centersplit = (
				((tri[j]->GetVtx(0)).Position)[splitdim]
				+ ((tri[j]->GetVtx(1)).Position)[splitdim]
				+ ((tri[j]->GetVtx(2)).Position)[splitdim] ) / 3;
			if (centersplit < splitpoint) {
				j++;
			}
			else {
				Triangle tmp = *tri[j];
				*tri[j] = *tri[k];
				*tri[k] = tmp;
				k--;
			}
		}
		count1 = j;
		if (count1 == 0) count1++;
		if (count1 == count) count1--;
		Child1 = new BoxTreeNode();
		Child2 = new BoxTreeNode();
		Child1->Construct(count1, &tri[0]);
		Child2->Construct(count-count1, &tri[count1]);
		return;
	}
}