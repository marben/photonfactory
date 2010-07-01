#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "Object3d.h"
#include "Point3d.h"
#include "Ray.h"
#include "config.h"
#include <iostream>
#include "Color.h"
#include "Light.h"
#include <vector>

namespace PF{

class Sphere: public Object3d{
	public:
		Sphere(){center=Point3d(0.0,0.0,0.0); r=1;}
		Sphere(const Point3d& _center, wfloat _r):center(_center),r(_r){}
		bool intersect(const Ray& r, wfloat& t, Vector3d& normal);
	protected:
		Point3d center;	// center of sphere
		wfloat r;	// radius
};

}	// namespace PF

#endif
