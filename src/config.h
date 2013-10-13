#ifndef _CONFIG_H_
#define _CONFIG_H_

#include "Image2d.h"
#include "ColorRGB.h"

namespace PF{

typedef float color_t;	// type used for representing one color channel
typedef double wfloat;	// type used for representing world units

typedef ggl::ColorRGB Color;

//typedef unsigned int uint;
typedef ggl::Canvas<PF::Color> Canvas;

#define PI 3.141592653589793238462f

#define DEBUG
//#define MEMSAFE	// used for proper destructors(maybe)

} // namespace PF

#endif
