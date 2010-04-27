#ifndef _SCREEN_H_
#define _SCREEN_H_

#include "Color.h"
#include "config.h"
#include "Point3d.h"
#include "Camera.h"

namespace PF{

class Screen{
	public:
		Screen();
		~Screen();
		unsigned int getX()const{return x;}
		unsigned int getY()const{return y;}
		void setX(const uint _x){x=_x;}
		void setY(const uint _y){y=_y;}
		int setColor(unsigned int x, unsigned int y, const Color c);
		void setColor(uint index, const Color& c);	// sets pixel number 'index'
		inline Color getColor(unsigned int x, unsigned int y)const;
		unsigned int getNumOfRays(){return x*y;}
		Color* getColors(){return *colors;}
		void init();

	private:
		Color** colors;
		unsigned int x,y;	// screen dimensions (dimensions of final render)

		int allocateColors();
};
		
Color Screen::getColor(uint _x, uint _y)const{
#ifdef DEBUG
	if(_x>x || _y>y){
		std::cerr<<"ERROR!!! indexing out of screen!!!"<<std::endl;
		return Color(1,0,1);
	}
#endif
	return colors[_x][_y];
}

}	// namespace PF

#endif
