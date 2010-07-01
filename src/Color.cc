#include "Color.h"
using namespace PF;

void Color::normalize(){
	if(red>1)
		red = 1;
	else
		if(red<0)
			red=0;

	if(green>1)
		green = 1;
	else
		if(green<0)
			green=0;

	if(blue>1)
		blue = 1;
	else
		if(blue<0)
			blue=0;
}
