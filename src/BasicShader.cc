#include "BasicShader.h"
#include <string>
#include "Vector3d.h"
#include <cmath>

using namespace std;
using namespace PF;

BasicShader::BasicShader(string name):Shader(name), color(), specularColor(), specularHardness(1),diffusion(0.5), specular(0.5), doubleSided(false), reflect(false), reflectionAmount(0.0){

}

vector<pair<Ray, color_t> > BasicShader::getSecondaryRays(const SurfacePoint& sp, const vector<Light*>& lights){
	vector<pair<Ray, color_t> > secondaryRays;
	if(reflect){	// mirror reflected ray
		Ray reflection(sp.getPoint(), sp.getViewer().getDirection().getReflection(sp.getNormal()));
		pair<Ray, color_t> p(reflection, reflectionAmount);
		//cout<<"ray "<<sp.getViewer()<<" reflects according to "<<sp.getNormal()<<" to "<<p.first<<endl;
		secondaryRays.push_back(p);
	}
	return secondaryRays;
}

Color BasicShader::shade(const SurfacePoint& surfacePoint, const vector<Light*>& lights){
	SurfacePoint surface(surfacePoint);
	if(doubleSided && dot(surface.getViewer().getDirection()*(-1), surface.getNormal())<0.0f){	// doublesided
		surface = SurfacePoint(surface.getPoint(), surface.getViewer(), surface.getNormal()*(-1));
	}
	Color c(0,0,0);
	//Color tmpColor;
	for(uint i = 0; i < lights.size(); i++){
		Ray lightRay(surface.getPoint(), lights[i]->getCenter());
		color_t diffuse = dot(surface.getNormal(),lightRay.getDirection());
		wfloat lightDistance = _distance(surface.getPoint(), lights[i]->getCenter());
		color_t intensity = lights[i]->getIntensity(lightDistance);
		intensity *= (color_t)lights[i]->getPower();
		c += diffusion * color * diffuse  * lights[i]->getColor()*intensity;	// diffuse

		// -- specular
		Vector3d lightReflection = lightRay.getDirection() * (-1);
		lightReflection = lightReflection.getReflection(surface.getNormal());
		lightReflection *= -1;
		wfloat d = dot(lightReflection, surface.getViewer().getDirection());
		if(d>0){
			color_t spec = specular * powf(d, specularHardness) * intensity;
			c += spec * lights[i]->getColor();
		}
		// -- end of specular

	}

	c.normalize();
	return c;
}
