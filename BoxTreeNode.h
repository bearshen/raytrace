#ifndef CSE168_BOXTREENODE_H
#define CSE168_BOXTREENODE_H
#include "Triangle.h"
#include "Ray.h"
#define MAX_TRIANGLES_PER_BOX 5
class BoxTreeNode {
public:
	BoxTreeNode() : NumTriangles(0) {};
	~BoxTreeNode() {
		for (int i = 0; i < NumTriangles; ++i) {
			if (Tri[i] != NULL) {
				delete Tri[i]; Tri[i] = NULL;
			}
		}
		if (Child1 != NULL) {
			delete Child1; Child1 = NULL;
		}
		if (Child2 != NULL) {
			delete Child2; Child2 = NULL;
		}
	};
	bool Intersect(const Ray &ray, Intersection &hit);
	void Construct(int count, Triangle **tri);
private:
	Vector3 BoxMin, BoxMax;
	BoxTreeNode *Child1, *Child2;
	Triangle *Tri[MAX_TRIANGLES_PER_BOX];
	int NumTriangles;
};
#endif