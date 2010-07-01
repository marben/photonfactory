#ifndef _POINT3D_H_
#define _POINT3D_H_

#include "config.h"
#include <cmath>
#include <iostream>

namespace PF{

struct Point3d{
		Point3d():x(0.0),y(0.0),z(0.0){}
		Point3d(wfloat _x, wfloat _y, wfloat _z):x(_x),y(_y),z(_z){}
		Point3d& operator *= (const wfloat c){x*=c;y*=c;z*=c;return *this;}
		wfloat getX(){return x;}
		wfloat getY(){return y;}
		wfloat getZ(){return z;}
		wfloat x, y, z;
};

inline Point3d operator - (const Point3d& a, const Point3d& b){
	return Point3d(a.x-b.x, a.y-b.y, a.z - b.z);
}

inline Point3d operator + (const Point3d& a, const Point3d& b){
	return Point3d(a.x + b.x, a.y + b.y, a.z + b.z);
}

inline const Point3d operator * (const Point3d& a, const wfloat c){
	return Point3d(a.x*c, a.y*c, a.z*c);
}

inline const Point3d operator * (const wfloat c, const Point3d& a){
	return Point3d(a.x*c, a.y*c, a.z*c);
}

/*
inline wfloat Point3d::distance(const Point3d& b)const{
	return (wfloat)sqrt((x*b.x)*(x*b.x) + (y*b.y)*(y*b.y) + (z*b.z)*(z*b.z));
}
*/
inline wfloat _distance(const Point3d& a, const Point3d& b){	// prekryva se s necim z std:: ; je treba zacit pouzivat namespacy. ted neni cas
	return (wfloat)sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y) + (a.z-b.z)*(a.z-b.z));
}

inline std::ostream& operator<<(std::ostream& stream, const Point3d& p){
	stream<<"["<<p.x<<","<<p.y<<","<<p.z<<"]";
	return stream;
}

}	// namespace PF
#endif
