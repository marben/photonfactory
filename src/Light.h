#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "Point3d.h"

namespace PF{

class Light{
	public:
		Light():center(), color(), shadow(false), power(0), fallOffQuad(1.0), fallOffLin(0.0), fallOffConst(0.0){}
		Light(const Point3d& c):center(c), color(0.6,0.6,0.6), shadow(false), power(0), fallOffQuad(1.0), fallOffLin(0.0), fallOffConst(0.0){}
		Light(const Point3d& c, const Color& col):center(c), color(col), shadow(false), power(0), fallOffQuad(1.0), fallOffLin(0.0), fallOffConst(0.0) {}
		Light(const Point3d& c, const Color& col, bool s):center(c), color(col), shadow(s), power(0), fallOffQuad(1.0), fallOffLin(0.0), fallOffConst(0.0){}
		void setColor(const Color& c){color = c;}
		void setColor(color_t r, color_t g, color_t b){color.setR(r); color.setG(g); color.setB(b);}
		void setCenter(const Point3d& _center){center = _center;}
		void setPower(uint pow){power=pow;}
		void setShadow(bool s=true){shadow=s;}
		color_t getIntensity(wfloat distance)const{return (wfloat)1.0f/(fallOffQuad*distance*distance+fallOffLin*distance+fallOffConst);}
		Point3d getCenter()const{return center;}
		Color getColor(){return color;}
		bool getShadow()const{return shadow;}
		uint getPower(){return power;}
	private:
		Point3d center;
		Color color;
		bool shadow;	// whether light casts shadows
		uint power;	// yafray - style light power(only quatratic falldown)
		color_t fallOffQuad, fallOffLin, fallOffConst;
};

}	// namespace PF

#endif
