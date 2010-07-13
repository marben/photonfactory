#include "Camera.h"
#include <iostream>
#include "Point3d.h"

using namespace std;
using namespace PF;

Ray Camera::getPrimaryRay(uint n){
// predpoklada pocatek vlevo nahore
	uint x = n % resX;
	uint y = n / resX;
	return Ray(from, Vector3d(from, getRealPoint(x,y)));
}

Point3d Camera::getRealPoint(uint px, uint py){
	uint halfPointsX = this->resX/2;
	uint halfPointsY = this->resY/2;
	Point3d point;
	point = to;
	point += ( worldResolution * ((wfloat)halfPointsX - (wfloat)px)) * vright;
	point += ( worldResolution * ((wfloat)halfPointsY - (wfloat)py)) * vup;
	return point;
}

Camera::Camera(const string& _name):from(), to(), up(), name(_name), resX(), resY(), focal(), vright(), vup(), vto(), worldResolution(){
	
}
void Camera::init(){
	this->vto=Vector3d(from, to);
	this->vup=Vector3d(from, up);
	this->vright = cross(vup, vto);
	//vup = cross(vto, vright);	// tak je to v yafrayi. proc?
	//vto.normalize();
	//vup.normalize();
	vright.normalize();
#ifdef DEBUG
	cout<<"vright:"<<vright<<endl;
	cout<<"vup:"<<vup<<endl;
	cout<<"vto:"<<vto<<endl;
#endif

	worldResolution = ((1/(wfloat)this->resX) / focal)*(this->vto).length();	// velikost pixelu v jednotkach sveta

#ifdef DEBUG
	cout<<"world resolution:"<<worldResolution<<endl;
#endif
}
