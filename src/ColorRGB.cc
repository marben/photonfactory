/*
 * PixelRGB.cc
 *
 *  Created on: Mar 5, 2009
 *      Author: gix
 */

#include "ColorRGB.h"

using namespace ggl;

void ColorRGB::normalize()
{
	if(_r > 1.0)
		_r = 1.0;
	else
		if(_r < 0.0)
			_r = 0.0;

	if(_g > 1.0)
		_g = 1.0;
	else
		if(_g < 0.0)
			_g = 0.0;

	if(_b > 1.0)
		_b = 1.0;
	else
		if(_b < 0.0)
			_b = 0.0;
}
