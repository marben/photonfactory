#include "Triangle.h"
#include <iostream>
#include <cmath>
#include "config.h"
#include "Triangle2d.h"
#include "Point2d.h"
#include "Point3d.h"
#include "Vector2d.h"

using namespace std;
using namespace PF;

bool Triangle::intersect(const Ray& r, wfloat& distance, Vector3d& normal){
	normal = this->getNormal();
	wfloat d = dot(r.getDirection(), normal);

	if( d ==0.0f )	// rovina trojuhelniku je rovnobezna s paprskem
		return false;

	distance = -(dot(Vector3d( *a, r.getOrigin()), normal) / d);	// vzdalenost ray.origin -> d*ray.dir
	if(distance < 0.0001f || distance > 99999999)	// moc blizko ci daleko --- potreba domyslet ty vzdalenosti
		return false;

// -- hledani nejlepsi projekce
	Point2d P, B, C;
	if(abs(normal.getX()) > abs(normal.getY())){
		if(abs(normal.getX()) > abs(normal.getZ())){	// omitting x axis (the biggest one)
			B.x = (*b).y - (*a).y;
			B.y = (*b).z - (*a).z;
			C.x = (*c).y - (*a).y;
			C.y = (*c).z - (*a).z;
			P.x = r.getOrigin().getY() + r.getDirection().getY() * distance - (*a).y;
			P.y = r.getOrigin().getZ() + r.getDirection().getZ() * distance - (*a).z;
		}
		else{	// omitting z axis
				B.x = (*b).x - (*a).x;
				B.y = (*b).y - (*a).y;
				C.x = (*c).x - (*a).x;
				C.y = (*c).y - (*a).y;
				P.x = r.getOrigin().getX() + r.getDirection().getX() * distance - (*a).x;
				P.y = r.getOrigin().getY() + r.getDirection().getY() * distance - (*a).y;
		}
	}
	else{
		if(abs(normal.getY()) > abs(normal.getZ())){	// omitting y axis
			B.x = (*b).x - (*a).x;
			B.y = (*b).z - (*a).z;
			C.x = (*c).x - (*a).x;
			C.y = (*c).z - (*a).z;
			P.x = r.getOrigin().getX() + r.getDirection().getX() * distance - (*a).x;
			P.y = r.getOrigin().getZ() + r.getDirection().getZ() * distance - (*a).z;
		}
		else{	// omitting z axis
			B.x = (*b).x - (*a).x;
			B.y = (*b).y - (*a).y;
			C.x = (*c).x - (*a).x;
			C.y = (*c).y - (*a).y;
			P.x = r.getOrigin().getX() + r.getDirection().getX() * distance - (*a).x;
			P.y = r.getOrigin().getY() + r.getDirection().getY() * distance - (*a).y;
		}
	}
// -- konec hledani nejlepsi projekce

	wfloat u = (P.y*C.x - P.x*C.y) / ( C.x*B.y - B.x*C.y );
	if(u<0.0f)
		return false;
	wfloat v = (P.x - u*B.x) / C.x;
	if(v<0.0f || v+u>1.0f)
		return false;

	return true;
}

void Triangle::countNormal(){
	this->normal = cross( Vector3d(*a,*b), Vector3d(*a,*c));
	this->normal.normalize();
}

