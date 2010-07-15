#ifndef _POINT3D_H_
#define _POINT3D_H_

#include "config.h"
#include <cmath>
#include <iostream>
#include <Eigen/Core>

namespace PF{

// uncomment following define, to use internal representation as 4d, which should help vectorisation
// currently, this seems to slow raytracer down by about 50%, but this might be due to wrong compiler flags

//#define VEC_3D_REPRESENTED_4D

#ifdef VEC_3D_REPRESENTED_4D
typedef Eigen::Matrix<wfloat, 4, 1> VectorInternalType;
#else
typedef Eigen::Matrix<wfloat, 3, 1> VectorInternalType;
#endif

class Point3d{
public:
		Point3d():_point(){}

		friend class Matrix4x4;

#ifdef VEC_3D_REPRESENTED_4D
		Point3d(wfloat x, wfloat y, wfloat z):_point(x, y, z, 1) {}
#else
		Point3d(wfloat x, wfloat y, wfloat z):_point(x, y, z) {}
#endif

		Point3d(const VectorInternalType & m) : _point(m) {}
		Point3d& operator *= (const wfloat c) {_point *= c; return *this;}
		wfloat getX() const {return _point.x();}
		wfloat getY() const {return _point.y();}
		wfloat getZ() const {return _point.z();}

		// these return modifiable reference
		wfloat& x() {return _point.x();}
		wfloat& y() {return _point.y();}
		wfloat& z() {return _point.z();}

		Point3d& operator += (const Point3d& b) {_point += b._point; return *this;}
		Point3d operator - (const Point3d& b) const { return Point3d(_point - b._point); }
		Point3d operator + (const Point3d& b) const { return Point3d(_point + b._point); }
		Point3d operator * (const wfloat& c) const { return Point3d(_point * c); }

		friend wfloat distance(const Point3d& a, const Point3d& b);

protected:
		VectorInternalType _point;
};

inline const Point3d operator * (const wfloat c, const Point3d& a)
{
	return a * c;
}


inline std::ostream& operator<<(std::ostream& stream, const Point3d& p)
{
	stream<<"["<<p.getX()<<","<<p.getY()<<","<<p.getZ()<<"]";
	return stream;
}

inline wfloat distance(const Point3d& a, const Point3d& b)
{
	VectorInternalType difference(a._point - b._point);

	return sqrt(difference.dot(difference));
}

}	// namespace PF
#endif
