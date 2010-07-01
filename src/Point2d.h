#ifndef _POINT2D_H_
#define _POINT2D_H_

#include "config.h"

namespace PF{

struct Point2d{
	public:
		Point2d():x(0),y(0){}
		Point2d(wfloat _x, wfloat _y):x(_x),y(_y){}

		Point2d operator - (const Point2d& a)const{return Point2d(x-a.x, y-a.y);}
		
		wfloat x,y;
};

}	// namespace PF

#endif
