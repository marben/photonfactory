#ifndef _CAMERA_H_
#define _CAMERA_H_


#include "config.h"
#include "Point3d.h"
#include "Vector3d.h"
#include <iostream>
#include "Ray.h"

namespace PF{

class Camera{
	public:
		Camera(const std::string& _name);
		void setFrom(const Point3d& _from){from = _from;}
		void setTo(const Point3d& _to){to = _to;}
		void setTop(const Point3d& _top){up = _top;}
		void setName(const std::string& _name){name = _name;}
		void setResolutionX(const uint r){resX = r;}
		void setResolutionY(const uint r){resY = r;}
		void setFocal(wfloat f){focal=f;}
		uint getPrimaryRaysNum(){return resX*resY;}
		Ray getPrimaryRay(uint n);
		uint getResolutionX()const{return resX;}
		uint getResolutionY()const{return resY;}

		Point3d getFrom(){return from;}
		void init();	// initializes all camera stuff(has to be called after all values are loaded
		Point3d getRealPoint(uint x, uint y);

	private:
		Point3d from, to, up;
		std::string name;
		uint resX, resY;	// resolution of the render

		wfloat focal;

		// -- testy podle yafraye(definice kamery je nejaka nejasna
		Vector3d vright, vup, vto;
		wfloat worldResolution;
};
}

#endif
