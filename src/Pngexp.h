#ifndef _PNGEXP_H_
#define _PNGEXP_H_

#include <png.h>
#include <iostream>
#include "Screen.h"

namespace PF{

class Pngexp{
	public:
		Pngexp():x(),y(){};
		bool exp(const Screen& sc, std::string filename);
	private:
		unsigned int x,y;
};

}	// namespace PF

#endif
