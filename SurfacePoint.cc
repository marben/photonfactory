#include "SurfacePoint.h"

using namespace PF;

SurfacePoint::SurfacePoint(const Point3d& _point, const Ray& _viewer, const Vector3d& _normal):point(_point),viewer(_viewer), normal(_normal){
	normal.normalize();
}
