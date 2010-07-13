#ifndef _VECTOR3D_H_
#define _VECTOR3D_H_

#include <Eigen/Core>

#include "config.h"
#include <cmath>
#include "Point3d.h"
#include <iostream>

namespace PF{

class Vector3d: public Point3d{
public:
		Vector3d() : Point3d() {}
		Vector3d(wfloat _x, wfloat _y, wfloat _z) : Point3d(_x, _y, _z) {}
		Vector3d(const Point3d& a) : Point3d(a) {}
		Vector3d(const Point3d& a, const Point3d& b) : Point3d(b.getX() - a.getX(), b.getY() - a.getY(), b.getZ() - a.getZ()) {}
		Vector3d(const Eigen::Matrix<wfloat, 3, 1>& m) : Point3d(m) {}

		Vector3d cross(const Vector3d& v)const {return Vector3d(getY() * v.getZ() - getZ() * v.getY(), getZ() * getX() - getX() * v.getZ(), getX() * v.getY() - getY() * v.getX());}	// cross product
		Vector3d getReflection(const Vector3d& normal)const;	// not yet tested well

		wfloat length() const {return sqrt(getX() * getX() + getY() * getY() + getZ() * getZ());}
		void normalize();

		Vector3d operator * (const wfloat& b) const
		{
			return Vector3d(this->_point * b);
		}

		wfloat dot(const Vector3d& b) const{
			return _point.dot(b._point);
		}

		// dot product
		wfloat operator * (const Vector3d& b) const
		{
			return this->dot(b);
		}
};


inline std::ostream& operator<<(std::ostream& stream, const Vector3d& v){
	stream<<"("<<v.getX()<<", "<<v.getY()<<", "<<v.getZ()<<")";
	return stream;
}


inline void Vector3d::normalize(){
	_point.normalize();
}

inline wfloat dot(const Vector3d& a, const Vector3d& b)
{
	return a.dot(b);
}

inline Vector3d cross(const Vector3d& v1, const Vector3d& v2)
{
	return Vector3d(v1.getY() * v2.getZ() - v1.getZ() * v2.getY(), v1.getZ() * v2.getX() - v1.getX() * v2.getZ(), v1.getX() * v2.getY() - v1.getY() * v2.getX());
}

inline Vector3d Vector3d::getReflection(const Vector3d& normal) const
{
	return Vector3d( this->_point - 2 * normal._point * this->_point.dot(normal._point) );
}

}	// namespace PF

#endif
