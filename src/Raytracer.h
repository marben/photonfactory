#ifndef _RAYTRACER_H_
#define _RAYTRACER_H_

#include "Scene.h"
#include "config.h"
#include "Pngexp.h"
#include <string>
#include "Object3d.h"
#include "Shader.h"
#include "Color.h"
#include <iostream>
#include <vector>

namespace PF{
	
class Raytracer{
	public:
		Raytracer(){_scene=NULL; _exportFile="output.png";}
		Raytracer(Scene *s, std::string out="output.png"):_scene(s){_exportFile=out;}
		Color raytrace(const Ray& ray, uint recursion=3);
		void render();

	private:
		bool findIntersection(const Ray& ray, Object3d** o, wfloat& t, Vector3d& normal);	// returns nearest intersection with object form scene->objects
		std::vector<Light*> findVisibleLights(const Point3d& X);	// takes shadows in mind
		Scene *_scene;
		std::string _exportFile;
};

}	// namespace PF

#endif
