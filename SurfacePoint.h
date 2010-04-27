#ifndef _SURFACEPOINT_H_
#define _SURFACEPOINT_H_

#include "config.h"
#include "Point3d.h"
#include "Vector3d.h"
#include "Ray.h"

namespace PF{

class SurfacePoint{
	public:
		SurfacePoint(const Point3d& _point, const Ray& _viewer, const Vector3d& _normal);
		SurfacePoint(const SurfacePoint& sp):point(sp.getPoint()), viewer(sp.getViewer()), normal(sp.getNormal()){}
		Vector3d getNormal()const{return normal;}
		Point3d getPoint()const{return point;}
		Ray getViewer()const{return viewer;}
	private:
		Point3d point;	// point on a surface
		Ray viewer;	// where does the viewer look from
		Vector3d normal;	// normal to a normal in a place of point
};

}	// namespace PF

#endif
