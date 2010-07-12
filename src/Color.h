#ifndef _COLOR_H_
#define _COLOR_H_

#include "config.h"
#include <ColorRGB.h>


/* every channel is represented as a float e <0,1>
 * when returning an unsigned int, value is e <0,255>
 * setting the color is similar
 */

namespace PF{

typedef ggl::ColorRGB Color;

}	// namespace PF
#endif
