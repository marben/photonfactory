#ifndef _POINT2D_H_
#define _POINT2D_H_

#include "config.h"
#include <Eigen/Core>

namespace PF{

class Point2d{
	public:
		Point2d(): _point(0, 0){}
		Point2d(wfloat x, wfloat y): _point(x, y) {}
		Point2d(const Eigen::Matrix<wfloat, 2, 1> point) : _point(point) {}

		wfloat getX() const {return _point.x();}
		wfloat getY() const {return _point.y();}

		// these return modifiable reference
		wfloat& x() {return _point.x();}
		wfloat& y() {return _point.y();}

		//Point2d operator - (const Point2d& a)const{return Point2d(x-a.x, y-a.y);}
		Point2d operator - (const Point2d& b) const { return Point2d(_point - b._point);}
		
		//wfloat x,y;
	protected:
		Eigen::Matrix<wfloat, 2, 1> _point;
};

}	// namespace PF

#endif
