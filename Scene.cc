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

using namespace std;
using namespace PF;

void Scene::init(){
	screen.setX(camera->getResolutionX());
	screen.setY(camera->getResolutionY());
	screen.init();
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
	return screen.getX()*screen.getY();
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

Shader* Scene::findShader(const string& name){
	for(uint i = 0; i< this->shaders.size(); i++){
		if(shaders[i]->getName() == name)
			return shaders[i];
	}
	cerr<<"couldn't find shader name: "<<name<<" ... something is wrong.."<<endl;
	return 0;
}

Scene::Scene(){
	backgroundColor = Color(0,0,0);
}
