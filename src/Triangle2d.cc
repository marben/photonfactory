#include "Triangle2d.h"
#include "Vector2d.h"
#include "Vector3d.h"

#include <iostream>
#include <cmath>

using namespace std;
using namespace PF;

bool Triangle2d::intersect(const Point2d& p){
 // pokus podle navodu
	wfloat denom = cross(a-c, b-c);
	wfloat u = cross(p-c, b-c)/denom;
	wfloat v = cross(a-c, p-c)/denom;
	if((u>=0)&&(u<=1)&&(v>=0)&&(v<=1)&&(u+v<1)){
//		cout<<"hit!"<<endl;
		return true;
	}
	return false;
 // -- pokus podle navodu

/*
	// zkusim opet implementaci pomoci uhlu
	Vector2d v1(p, a);
	Vector2d v2(p, b);
	Vector2d v3(p, c);
	v1.normalize();
	v2.normalize();
	v3.normalize();
	wfloat r1 = dot(v1, v2);
	wfloat r2 = dot(v2, v3);
	wfloat r3 = dot(v3, v1);
	r1 = acos(r1);
	r2 = acos(r2);
	r3 = acos(r3);
	//cout<<r1<<" "<<r2<<" "<<r3<<endl;
	if( r1+r2+r3 > 2*PI-0.1){
		//cout<<"hit!"<<endl;
		return true;
	}
	return false;
*/

}


// asi nebude potreba
wfloat Triangle2d::normalLength(){
	Vector3d v1(a.getX(), a.getY(), 0);
	Vector3d v2(b.getX(), b.getY(), 0);
	v1 = cross(v1, v2); // ! hack ! tady to jde optimalizovat, az bude fungovat Vector3d.cross(const Vector3d&) tak jak ma
	return v1.length();
}
