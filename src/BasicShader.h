#ifndef _BASICSHADER_H_
#define _BASICSHADER_H_

#include "config.h"
#include "Shader.h"
#include "Color.h"
#include "SurfacePoint.h"
#include "Ray.h"
#include "Light.h"
#include <string>
#include <vector>

namespace PF{

class BasicShader: public PF::Shader{
	public:
		BasicShader(std::string name);
		~BasicShader(){}
		void setColor(const Color& _color){color = _color;}
		Color shade(const SurfacePoint& surfacePoint, const std::vector<Light*>& lights);
		std::vector<std::pair<Ray,color_t> > getSecondaryRays(const SurfacePoint& surfacePoint, const std::vector<Light*>& lights);
		void setColor(color_t r, color_t g, color_t b){color = Color(r,g,b);}
		void setDiffusion(color_t diff){diffusion = diff;}
		void setSpecular(color_t spec){specular = spec;}
		void setSpecularColor(const Color& c){color = c;}
		void setSpecularHardness(const int hardness){specularHardness=hardness;}
		void setDoubleSided(const bool var=true){doubleSided=var;}
		void setReflect(const bool ref=true){reflect=ref;}
		void setReflectionAmount(const color_t var){reflectionAmount=var;}
		Color getColor()const{return color;}
		color_t getSpecular()const{return specular;}
		bool getReflect()const{return reflect;}

private:
		Color color;
		Color specularColor;
		int specularHardness;
		color_t diffusion;
		color_t specular;
		bool doubleSided;	// whether material is doublesided or only works on one side
		bool reflect;	// whe material reflects light
		color_t reflectionAmount;
};

}	// namespace PF
#endif
