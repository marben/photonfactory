#ifndef _YAFIMPORT_H_
#define _YAFIMPORT_H_

#include "config.h"
#include "Scene.h"
#include "Point3d.h"
#include "Triangle.h"
#include "Camera.h"
#include "Shader.h"
#include "Matrix4x4.h"
#include <vector>

#include <iostream>
#include <vector>
#include <libxml/xmlreader.h>

namespace PF{

class YafImport{
	public:
		Scene* import(const std::string);

	private:
		bool tagEqual(const char* name);	// returns true if actual tag && name are equal
		bool isEndTag();	// returns true if actual tag is a end tag
		bool isStartTag();
		int loadScene();
		int loadTransform();
		int loadObject(const Matrix4x4& transform);
		int loadShader();
		int loadCamera();
		int loadLight();
		int loadBackground();
		int initPoints(std::vector< std::pair<Point3d*, int> >&);	// copies all points to this->scene
		Point3d* loadPoint(const Matrix4x4& transform=Matrix4x4(1));
		std::string getAttribute(const char* name);
		wfloat getAttributeFloat(const char* name);
		int freeUnusedPoints(std::vector< std::pair<Point3d*, int> >&);	// frees memory of Points with pair.second == 0. returns number of freed points(and gives used ones to scene.points

		void makePointsSpheres();	// for testing only. Makes a sphere around every point
		xmlTextReaderPtr reader;
		Scene* scene;
};

} // namespace PF 

#endif
