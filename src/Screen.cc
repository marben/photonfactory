#include "Screen.h"
#include <iostream>

namespace PF {

int Screen::setColor(unsigned x, unsigned y, Color c){
	_image.putPixel(x, y, c);
	return 0;
}

void Screen::setColor(unsigned number, const Color& color){
	_image.putPixel(number % getWidth(), number / getWidth(), color);
}

}	// namespace PF
