#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include "Object3d.h"
#include "Point3d.h"
#include "Vector3d.h"
#include "Triangle2d.h"
#include <vector>

namespace PF{

class Triangle: public Object3d{
	public:
		Triangle(Point3d* _a, Point3d* _b, Point3d* _c):a(_a), b(_b), c(_c){countNormal();}

		bool intersect(const Ray&, wfloat& t, Vector3d& normal);

		Vector3d getNormal(){return normal;}
		Point3d* getA(){return a;}
		Point3d* getB(){return b;}
		Point3d* getC(){return c;}

	private:
		void countNormal();

		Point3d *a,*b,*c;
		Vector3d normal;
};

}	// namespace PF

#endif
