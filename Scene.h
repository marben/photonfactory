#ifndef _SCENE_H_
#define _SCENE_H_

#include <string>
#include <vector>
#include "Object3d.h"
#include "Screen.h"
#include "Light.h"
#include "Plane.h"
#include "config.h"
#include "Point3d.h"
#include "Shader.h"
#include "Camera.h"

namespace PF{

class Scene{
	public:
		void addObject3d(Object3d* o);
		void addLight(Light*);
		void addShader(Shader* s);
		void setBackgroundColor(const Color& col){backgroundColor=col;}
		Color getBackgroundColor()const{return backgroundColor;}
		unsigned int getPrimaryRaysNum()const;
		Camera& getCamera()const{return *camera;}
		unsigned int objectsNumber()const{return objects.size();}
		unsigned int vertexNumber()const{return points.size();}
		Shader* findShader(const std::string& name);
		Scene();
		void init();	// necessary initialization after scene is loaded
		~Scene();
	//protected:
		std::vector<Object3d*> objects;
		std::vector<Light*> lights;
		std::vector<Point3d*> points;
		std::vector<Shader*> shaders;
	public:
		Screen screen;
		Camera* camera;
		Color backgroundColor;	// constnt background color for rendering
};

}	// namespace PF

#endif
