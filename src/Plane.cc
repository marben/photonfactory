#include "Plane.h"

using namespace PF;

bool Plane::intersect(const Ray& r, wfloat& t, Vector3d& normal){
	normal=this->n;
	wfloat don = dot(this->n, r.getDirection());
	//if(d >= 0)
	//	return false;
	if(don == 0)	// jsou rovnobezne, ale je treba jeste otestovat, jestli nahodou Ray nelezi na plose. co pak vracet?
		return false;
	//t = dot(normal, a-r.getOrigin())/ dot(normal, r.getDirection());
	t = dot(normal, a - r.getOrigin()) / dot(normal, r.getDirection());
	return true;
}

Plane::Plane() : Object3d()
{
}


Plane::~Plane()
{
}

