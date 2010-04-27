#ifndef _VECTOR3D_H_
#define _VECTOR3D_H_

#include "config.h"
#include <cmath>
#include "Point3d.h"
#include <iostream>

namespace PF{

struct Vector3d: public Point3d{
		Vector3d():Point3d(){}
		Vector3d(wfloat _x, wfloat _y, wfloat _z):Point3d(_x, _y, _z){}
		Vector3d(const Point3d& a):Point3d(a){}
		Vector3d(const Point3d& a, const Point3d& b):Point3d(b.x-a.x, b.y-a.y, b.z-a.z){}
		Vector3d cross(const Vector3d& v)const {return Vector3d(y*v.z-z*v.y, z*x-x*v.z, x*v.y-y*v.x);}	// cross product
		Vector3d getReflection(const Vector3d& normal)const;	// not yet tested well

		wfloat length(){return sqrt(x*x + y*y + z*z);}
		void normalize();
};


inline std::ostream& operator<<(std::ostream& stream, const Vector3d& v){
	stream<<"("<<v.x<<", "<<v.y<<", "<<v.z<<")";
	return stream;
}

inline void Vector3d::normalize(){
	wfloat l = sqrt(x*x + y*y + z*z);
	x /= l;
	y /= l;
	z /= l;
}

inline wfloat operator * (const Vector3d& a, const Vector3d& b){
	return (a.x*b.x + a.y*b.y + a.z*b.z);
}

inline wfloat dot(const Vector3d& a, const Vector3d& b){
	return (a.x*b.x + a.y*b.y + a.z*b.z);
}

inline Vector3d cross(const Vector3d& v1, const Vector3d& v2)
{
	return Vector3d(v1.y*v2.z-v1.z*v2.y, v1.z*v2.x-v1.x*v2.z, v1.x*v2.y-v1.y*v2.x);
}

inline Vector3d Vector3d::getReflection(const Vector3d& normal)const
{
	return Vector3d((*this) - 2 * dot((*this),normal) * normal);
}

/*
inline Vector3d reflect(const Vector3d& v, const Vector3d& normal){	// not yet tested
	return Vector3d(v - 2 * dot(v,normal) * normal);
}
*/

}	// namespace PF

#endif
