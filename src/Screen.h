#ifndef _SCREEN_H_
#define _SCREEN_H_

#include "Image2d.h"

#include "config.h"
#include "Point3d.h"
#include "Camera.h"

namespace PF{

class Screen{
	public:
		unsigned getWidth() const {return _image.width();}
		unsigned getHeight() const {return _image.height();}

		void setResolution(unsigned width, unsigned height) {_image.resize(width, height);}
		int setColor(unsigned x, unsigned y, const Color c);
		void setColor(unsigned index, const Color& c);	// sets pixel number 'index'

		// gets the color of a pixel
		inline Color getColor(unsigned int x, unsigned int y)const;

		// gets the whole canvas
		const Canvas& getCanvas() const {return _image;}

	private:

		ggl::Image2d<Color> _image;
};
		
Color Screen::getColor(unsigned x, unsigned y)const{
#ifdef DEBUG
	if(x > _image.width() || y > _image.height()){
		std::cerr<<"ERROR!!! indexing out of screen!!!"<<std::endl;
		return Color(1,0,1);
	}
#endif
	return _image.getPixel(x, y);
}

}	// namespace PF

#endif
