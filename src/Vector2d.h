#ifndef _VECTOR2D_H_
#define _VECTOR2D_H_

#include "config.h"
#include "Point2d.h"
#include <cmath>

namespace PF{

struct Vector2d: public Point2d{
	public:
		Vector2d():Point2d(){}
		Vector2d(wfloat _x, wfloat _y):Point2d(_x, _y){}
		Vector2d(const Point2d& p):Point2d(p){}
		Vector2d(const Point2d& a, const Point2d& b):Point2d(b.x-a.x, b.y-a.y){}
		wfloat length();
		void normalize();
};

inline wfloat cross(const Vector2d& a, const Vector2d& b){
	return (a.x*b.y-a.y*b.x);
}
inline wfloat dot(const Vector2d& a, const Vector2d& b){
	return (a.x*b.x+a.y*b.y);
}

inline void Vector2d::normalize(){
	wfloat l = sqrt(x*x + y*y);
	x /= l;
	y /= l;
}

inline wfloat Vector2d::length(){
	return sqrt(x*x + y*y);
}

}	// namespace PF

#endif
