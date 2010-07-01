#ifndef PLANE_H
#define PLANE_H

#include "Object3d.h"

namespace PF{

// funguje nejak totalne spatne, radeji asi nepouzivat, stejne do budoucna asi existovat nebude
class Plane : public Object3d
{
	public:
		Plane();
		Plane(const Point3d& _a, const Vector3d& _n): a(_a), n(_n){}
		~Plane();
		bool intersect(const Ray&, wfloat& t, Vector3d& normal);
		
		Point3d a;
		Vector3d n;	// normalovej vektor
};

}	// namespace PF

#endif
