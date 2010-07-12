#include "Raytracer.h"
#include "Shader.h"
#include "Camera.h"

#include "Triangle.h"
#include "SurfacePoint.h"
#include "BasicShader.h"

#include <PngWriter.h>	// ggl

using namespace std;
using namespace PF;

Color Raytracer::raytrace(const Ray& ray, uint recursion){
	wfloat t;
	Object3d* o=NULL;
	Vector3d normal;

	if(findIntersection(ray, &o, t, normal)){
		Point3d xPoint(ray.getOrigin() + t * ray.getDirection());
		vector<Light*> visibleLights = findVisibleLights(xPoint);
		SurfacePoint sp(xPoint, ray, normal);
		Shader* sh = o->getShader();
		Color color = ((BasicShader*)sh)->shade(sp, visibleLights);	// raytraced shader is always BasicShader(so far)

		// -- reflection, refraction...
		if(((BasicShader*)sh)->getReflect() && recursion>0){
			vector<std::pair<Ray,color_t> > secondaryRays = (((BasicShader*)sh)->getSecondaryRays(sp, visibleLights));
			recursion--;
			for(uint i=0; i<secondaryRays.size();i++){
				color +=raytrace(secondaryRays[i].first, recursion)*secondaryRays[i].second;
			}
		}

		return color;
	}
	return _scene->getBackgroundColor();
}

void Raytracer::render(){
	Camera& camera = _scene->getCamera();
	for(uint i=0; i<camera.getPrimaryRaysNum();i++){
		Ray ray = camera.getPrimaryRay(i);
		Color color = raytrace(ray);
		_scene->screen.setColor(i, color);
	}

// exporting should be outside raytracer...but not for now...
	Pngexp exporter;
	ggl::PngWriter writer(_exportFile);
	exporter.exp(_scene->screen, _exportFile);
}

vector<Light*> Raytracer::findVisibleLights(const Point3d& xPoint){		// ted s novejma shaderama nefungujou stiny a vubec .. nutno prepsat
	vector<Light*> allLights = _scene->lights; // ! hack ! tak tady to chce urcite optimalizovat
	vector<Light*> visibleLights;	// sem budu pridavat svetla, ktera vidim
	Vector3d normal;
	uint dontAdd;
	for(uint l=0; l<allLights.size();l++){
		dontAdd=0;
		if(!allLights[l]->getShadow()){
			visibleLights.push_back(allLights[l]);
			continue;
		}
		Ray rayToLight(xPoint, allLights[l]->getCenter());
		for(uint o=0; o < _scene->objects.size(); o++){
			wfloat distance;
			if(_scene->objects[o]->intersect(rayToLight, distance, normal)){	// should be shorten(explicit because of debugging :(  )
				wfloat intersectDistance=_distance(Point3d((rayToLight.getOrigin()+distance*rayToLight.getDirection())), xPoint);
				if(intersectDistance > 0.00001){
					wfloat lightDistance = _distance(xPoint, allLights[l]->getCenter());
					if(intersectDistance < lightDistance){
						dontAdd++;
					}
				}
			}
		}
		if(!dontAdd){
			visibleLights.push_back(allLights[l]);
		}
	}
	return visibleLights;
}

bool Raytracer::findIntersection(const Ray& ray, Object3d** o, wfloat& t, Vector3d& normal){
	wfloat min_t = 9999999; // ! hack !, je treba nejak poresit maximalni vzdalenost
	Vector3d tmp_normal;
	for(uint i=0; i<_scene->objects.size(); i++){
		if(_scene->objects[i]->intersect(ray, t, tmp_normal))	// ! hack ! ta podminka by nemusela bejt nutna..asi
			if((t<min_t)){// && (t>0.000001f)){	// ! hack ! - treba nejak poresit minimalni epsilon
					min_t = t;
					*o = _scene->objects[i];
					normal = tmp_normal;
			}
	}

	if(min_t != 9999999){
		t = min_t;
		return true;
	}

	return false;
}
