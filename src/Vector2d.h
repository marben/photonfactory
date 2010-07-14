#ifndef _VECTOR2D_H_
#define _VECTOR2D_H_

#include "config.h"
#include "Point2d.h"
#include <cmath>

namespace PF{

class Vector2d: public Point2d{
	public:
		Vector2d():Point2d(){}
		Vector2d(wfloat _x, wfloat _y):Point2d(_x, _y){}
		Vector2d(const Point2d& p):Point2d(p){}
		//Vector2d(const Point2d& a, const Point2d& b) : Point2d(b.x-a.x, b.y-a.y){}
		Vector2d(const Point2d& a, const Point2d& b) : Point2d(b - a){}

		wfloat dot(const Vector2d& b) const {return this->_point.dot(b._point);}

		wfloat length() const;
		void normalize();
};


inline wfloat cross(const Vector2d& a, const Vector2d& b)
{
	return (a.getX() * b.getY() - a.getY() * b.getX());
	//return a._point.cross(b._point);
}


inline wfloat dot(const Vector2d& a, const Vector2d& b){
	//return (a.x*b.x+a.y*b.y);
	//return a._point.dot(b._point);
	return a.dot(b);
}

inline void Vector2d::normalize(){

	wfloat l = sqrt(x()*x() + y()*y());
	x() /= l;
	y() /= l;

	//_point.normalize();
}

inline wfloat Vector2d::length() const {
	//return sqrt(x*x + y*y);
	//Eigen::Matrix<wfloat, 2, 1> difference;
	return sqrt(_point.dot(_point));
}

}	// namespace PF

#endif
