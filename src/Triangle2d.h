#ifndef _TRIANGLE2D_H_
#define _TRIANGLE2D_H_

#include "config.h"
#include "Point2d.h"

namespace PF{

class Triangle2d{
	public:
		Triangle2d(){};
		Triangle2d(const Point2d& _a, const Point2d& _b, const Point2d& _c):a(_a),b(_b),c(_c){}
		Triangle2d(wfloat ax, wfloat ay, wfloat bx, wfloat by, wfloat cx, wfloat cy):a(ax,ay),b(bx,by),c(cx,cy){}
		wfloat normalLength();
		bool intersect(const Point2d&);
	protected:
		Point2d a,b,c;
};

}	// namespace PF

#endif
