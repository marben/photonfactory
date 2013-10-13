#ifndef _RAYTRACER_H_
#define _RAYTRACER_H_

#include "Scene.h"
#include "config.h"
#include <string>
#include "Object3d.h"
#include "Shader.h"
#include <iostream>
#include <vector>
#include <memory>
#include "Image2d.h"

namespace PF{
	
class Raytracer{
	public:
		Color raytrace(const Scene& scene, const Ray& ray, uint recursion=3);
		std::auto_ptr< Screen > render(const Scene&);

	private:
		bool findIntersection(const Scene& scene, const Ray& ray, Object3d** o, wfloat& t, Vector3d& normal);	// returns nearest intersection with object form scene->objects
		std::vector<Light*> findVisibleLights(const Scene& scene, const Point3d& X);	// takes shadows in mind
};

}	// namespace PF

#endif
