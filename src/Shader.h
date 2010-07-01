#ifndef _SHADER_H_
#define _SHADER_H_

#include "Point3d.h"
#include "Vector3d.h"
#include "Light.h"
#include "SurfacePoint.h"
#include "Color.h"
#include <vector>
#include <string>

namespace PF{

class Shader{
	public:
		Shader():name("default shader"){}
		Shader(std::string _name):name(_name){}
		virtual Color shade(const SurfacePoint& surfacePoint, const std::vector<Light*>& lights)=0;
		virtual ~Shader(){}

		void setName(const std::string& n){name=n;}
		std::string getName(){return name;}


		std::string name;	// shader name
};

}

#endif
