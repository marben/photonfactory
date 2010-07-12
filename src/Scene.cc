#include <iostream>
#include "Scene.h"
#include "Sphere.h"
#include "Point3d.h"
#include "Vector3d.h"
#include "Pngexp.h"
#include "Ray.h"
#include "Triangle.h"
#include "Shader.h"
#include "BasicShader.h"
#include "Camera.h"

namespace PF {

void Scene::init(){
	screen.setResolution(camera->getResolutionX(), camera->getResolutionY());
}

void Scene::addObject3d(Object3d* o){
	if(o->getShader()==NULL)
		std::cerr<<"Error: object has no assigned shader!!";
	objects.push_back(o);
}

void Scene::addLight(Light* l){
	lights.push_back(l);
}

void Scene::addShader(Shader* s){
	shaders.push_back(s);
}

uint Scene::getPrimaryRaysNum()const{
	return screen.getWidth()*screen.getHeight();
}
Scene::~Scene(){
	// old-kool deleting of vectors of pointers
	for(unsigned int i=0; i<objects.size();i++)
		delete objects[i];

	for(unsigned int i=0; i<lights.size();i++)
		delete lights[i];

	for(unsigned int i=0; i<points.size();i++)
		delete points[i];
/*
	for(unsigned int i=0; i<shaders.size();i++)
		if(shaders[i]!=0)
			delete shaders[i];
*/

	delete camera;
}

Shader* Scene::findShader(const std::string& name){
	for(uint i = 0; i< this->shaders.size(); i++){
		if(shaders[i]->getName() == name)
			return shaders[i];
	}
	std::cerr<<"couldn't find shader name: "<<name<<" ... something is wrong.."<<std::endl;
	return 0;
}


Scene::Scene()
{
	backgroundColor = Color(0,0,0);
}

}	// namespace PF
