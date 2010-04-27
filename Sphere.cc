#include "Sphere.h"
#include <cmath>
#include "Color.h"
#include "Vector3d.h"

using namespace std;
using namespace PF;


bool Sphere::intersect(const Ray& r, wfloat& t, Vector3d& normal){
	wfloat a = r.getDirection()*r.getDirection();
	Vector3d V = r.getOrigin() - this->center;
	wfloat b = 2.0*(V*r.getDirection());
	wfloat c = (V*V) - (this->r*this->r);
	wfloat det = b*b - 4.0*a*c;
	if(det < 0)
		return false;
	t = ((-b) - sqrt(det))/(2*a); // ! hack ! predpoklada, ze kamera neni uvnitr koule
	Point3d X(r.getOrigin()+r.getDirection()*t);
	normal=Vector3d(this->center, X);
	normal.normalize();
	return true;
}
