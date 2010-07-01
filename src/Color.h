#ifndef _COLOR_H_
#define _COLOR_H_

#include "config.h"


/* every channel is represented as a float e <0,1>
 * when returning an unsigned int, value is e <0,255>
 * setting the color is similar
 */

namespace PF{

class Color{
	public:
		color_t getR()const{return red;}
		color_t getG()const{return green;}
		color_t getB()const{return blue;}
		void setR(color_t r){red=r;}
		void setG(color_t g){green=g;}
		void setB(color_t b){blue=b;}
		unsigned int getR_int()const;
		unsigned int getG_int()const;
		unsigned int getB_int()const;
		Color(color_t _r=0, color_t _g=0, color_t _b=0):red(_r),green(_g),blue(_b){}
		bool isBlack(){return ((red==0)&&(blue==0)&&(green==0))?true:false;}
		void normalize();	// sets values <0 to 0 and vlues > 1 to 1
		void filter(const Color& col);	// filters *this color with col (no value can be higher than col's
		Color operator * (const color_t& par) const;
		Color& operator *= (const color_t& par);
		Color& operator += (const Color& c);
		Color operator * (const Color&) const;
		friend Color operator*(color_t, const Color& c);

		color_t red,green,blue;
};

inline void Color::filter(const Color& col){
	if(red>col.getR())
		red = col.getR();

	if(green>col.getG())
		green = col.getG();

	if(blue>col.getB())
		blue = col.getB();

	return;
}

inline Color operator*(color_t a, const Color& c){
	return Color(c.red * a, c.green * a, c.blue * a);
}

inline Color Color::operator * (const Color& c) const{
	return Color(red*c.red, green*c.green, blue*c.blue);
}

inline Color& Color::operator += (const Color& c){
	red+=c.red;
	green+=c.green;
	blue+=c.blue;
	normalize();
	return *this;
}

inline Color Color::operator * (const color_t& par) const{
	if(par<=0)
		return Color(0.0,0.0,0.0);
	return Color(red*par, green*par, blue*par);
}

inline unsigned int Color::getR_int()const{
	return (unsigned int) (255*red);
}

inline unsigned int Color::getG_int()const{
	return (unsigned int) (255*green);
}

inline unsigned int Color::getB_int()const{
	return (unsigned int) (255*blue);
}

inline Color& Color::operator *= (const color_t& par){
	if(par<=0){
		red = green = blue = 0.0;
		return *this;
	}
	red *= par;
	green *= par;
	blue *= par;
	return *this;
}

}	// namespace PF
#endif
