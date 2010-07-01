#ifndef _RAY_H_
#define _RAY_H_

#include "Point3d.h"
#include "Vector3d.h"
#include <iostream>

namespace PF{

class Ray{	// defined by origin and vector
	public:
		Ray():origin(0,0,0), dir(0,0,0){}
		Ray(const Point3d& a, const Vector3d& v):origin(a), dir(v){dir.normalize();}
		Ray(const Point3d& a, const Point3d& b):origin(a),dir(b-a){dir.normalize();}
		Point3d getOrigin()const{return origin;}
		Vector3d getDirection()const{return dir;}
	private:
		Point3d origin;
		Vector3d dir;
};

inline std::ostream& operator<<(std::ostream& ost, const Ray& ray){
	ost<<ray.getOrigin()<<"->"<<ray.getDirection();
	return ost;
}

}

#endif
