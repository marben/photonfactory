#include "YafImport.h"
#include <cstdlib>
#include <iostream>
#include <libxml/xmlreader.h>
#include <cstring>
#include <vector>
#include "Triangle.h"
#include "Shader.h"
#include "Sphere.h"
#include "Camera.h"
#include "BasicShader.h"
#include "Matrix4x4.h"
#include "Plane.h"


using namespace std;
using namespace PF;

int YafImport::loadCamera(){
	Camera* camera = new Camera(getAttribute("name"));

	camera->setResolutionX((uint)getAttributeFloat("resx"));
	camera->setResolutionY((uint)getAttributeFloat("resy"));
	camera->setFocal(getAttributeFloat("focal"));
	while(!(tagEqual("camera") && isEndTag())){
		if(tagEqual("from") && isStartTag())
			camera->setFrom(Point3d(getAttributeFloat("x"), getAttributeFloat("y"), getAttributeFloat("z")));
		if(tagEqual("to") && isStartTag())
			camera->setTo(Point3d(getAttributeFloat("x"), getAttributeFloat("y"), getAttributeFloat("z")));
		if(tagEqual("up") && isStartTag())
			camera->setTop(Point3d(getAttributeFloat("x"), getAttributeFloat("y"), getAttributeFloat("z")));
		xmlTextReaderRead(reader);
	}
	camera->init();	// this must be called
	scene->camera = camera;
	return 0;
}


Point3d* YafImport::loadPoint(const Matrix4x4& transform){
	if(xmlTextReaderAttributeCount(reader) != 3){
		cerr<<"error loading vertex"<<endl;
		return NULL;
	}
	Point3d* p = new Point3d(getAttributeFloat("x"), getAttributeFloat("y"), getAttributeFloat("z"));
	transform.transform(*p);
#ifdef DEBUG
//	cout<<"loading point: "<<*p<<endl;
#endif
	return  p;
}

int YafImport::loadBackground(){
	while(!(tagEqual("background") && isEndTag())){
		xmlTextReaderRead(reader);
		if(tagEqual("color")){
			scene->setBackgroundColor(Color(getAttributeFloat("r"), getAttributeFloat("g"), getAttributeFloat("b")));
		}
	}

	return 0;
}

int YafImport::loadObject(const Matrix4x4& transform){

	vector< pair<Point3d*, int> > points;
	vector< Triangle* > myTriangles;

	Shader* shader = scene->findShader(getAttribute("shader_name"));

	while(!(tagEqual("object") && isEndTag())){
		xmlTextReaderRead(reader);
		if(tagEqual("p")&&isStartTag()){
			points.push_back( pair<Point3d*, int>(loadPoint(transform),0));
			continue;
		}

		if(tagEqual("f")&&isStartTag()){
			scene->addObject3d(
					new Triangle( points[(int)getAttributeFloat("a")].first,
					 	points[(int)getAttributeFloat("b")].first,
						points[(int)getAttributeFloat("c")].first)
					);
			points[(int)getAttributeFloat("a")].second=1;
			points[(int)getAttributeFloat("b")].second=1;
			points[(int)getAttributeFloat("c")].second=1;

			(scene->objects[scene->objects.size()-1])->setShader(shader);

			continue;
		}
	}

	freeUnusedPoints(points);
	initPoints(points);

	return 0;
}

void YafImport::makePointsSpheres(){
	cout<<"creating spheres from points"<<endl;
	BasicShader* shader = new BasicShader("shader1");
	shader->setColor(1,0,0);
	for(unsigned int i=0; i<scene->vertexNumber();i++){
		Object3d* o = new Sphere(*(scene->points[i]),0.2);
		o->setShader(shader);
		scene->addObject3d(o);
	}
}

int YafImport::loadShader(){
	BasicShader* shader = new BasicShader(getAttribute("name"));
	shader->setName(getAttribute("name"));
#ifdef DEBUG
	cout<<"loading shader name: "<<shader->getName()<<endl;
#endif
	while(!(tagEqual("shader") && isEndTag())){
		if(tagEqual("color")){
			shader->setColor(getAttributeFloat("r"), getAttributeFloat("g"), getAttributeFloat("b"));
		}
		if(tagEqual("diffuse_reflect")){
			shader->setDiffusion(getAttributeFloat("value"));
		}
		if(tagEqual("mirror_color")){
			//shader->setReflection(getAttributeFloat("value"));
		}
		if(tagEqual("specular_amount")){
			shader->setSpecular(getAttributeFloat("value"));
		}
		if(tagEqual("hard")){
			shader->setSpecularHardness((int)getAttributeFloat("value"));
		}
		if(tagEqual("reflect")){
			if(getAttribute("value") == "on")
				shader->setReflect(true);
		}
		if(tagEqual("reflect_amount")){
			shader->setReflectionAmount(getAttributeFloat("value"));
		}

		xmlTextReaderRead(reader);
	}

	shader->setDoubleSided(true);	// it seems that all blender materials are doublesided(needs further investigation)
	scene->addShader(shader);

	return 0;
}

int YafImport::loadTransform(){
	Matrix4x4 matrix;
	matrix.setRow(0, getAttributeFloat("m00"), getAttributeFloat("m01"), getAttributeFloat("m02"), getAttributeFloat("m03"));
	matrix.setRow(1, getAttributeFloat("m10"), getAttributeFloat("m11"), getAttributeFloat("m12"), getAttributeFloat("m13"));
	matrix.setRow(2, getAttributeFloat("m20"), getAttributeFloat("m21"), getAttributeFloat("m22"), getAttributeFloat("m23"));
	matrix.setRow(3, getAttributeFloat("m30"), getAttributeFloat("m31"), getAttributeFloat("m32"), getAttributeFloat("m33"));
	xmlTextReaderRead(reader);
	while(!(tagEqual("transform") && isEndTag())){
		if(tagEqual("object") && isStartTag()){
			if(loadObject(matrix))
				return 1;
			continue;
		}

		xmlTextReaderRead(reader);
	}
	return 0;
}

int YafImport::loadScene(){
	if((!tagEqual("scene")) || (!isStartTag())){
		cerr<<"wrong xml file"<<endl;
		return 1;
	}
	scene = new Scene();

	while(!(tagEqual("scene") && isEndTag())){	// ! hack ! have to check end of file before </scene> (same with others tags)

		if(tagEqual("transform") && isStartTag()){
			if(loadTransform())
				return 1;
			continue;
		}
		if(tagEqual("shader") && isStartTag()){
			if(loadShader())
				return 1;
			continue;
		}
		if(tagEqual("camera") && isStartTag()){
			if(loadCamera())
				return 1;
			continue;
		}
		if(tagEqual("light") && isStartTag()){
			if(loadLight())
				return 1;
			continue;
		}
		if(tagEqual("background") && isStartTag()){
			if(loadBackground())
				return 1;
			continue;
		}

		xmlTextReaderRead(reader);
	}

	// ! hack !/
	//makePointsSpheres();
	//scene->addObject3d(new Plane(Point3d(0,0,0), Vector3d(1,1,0)));
	
	scene->init();
	return 0;
}
int YafImport::loadLight(){
	Light* light = new Light();
	light->setPower((uint)getAttributeFloat("power"));
	if(getAttribute("cast_shadows") == "on"){
		light->setShadow(true);
	}
	while(!(tagEqual("light") && isEndTag())){
		if(tagEqual("from")&&isStartTag()){
			Point3d *p = loadPoint();	// ! hack ! -- kind of....non-elegant
			light->setCenter(*p);
			delete p;
		}
		if(tagEqual("color")&&isStartTag()){
			light->setColor(Color((color_t)getAttributeFloat("r"), (color_t)getAttributeFloat("g"), (color_t)getAttributeFloat("b")));
		}
		xmlTextReaderRead(reader);
	}
	scene->addLight(light);
	return 0;
}

Scene* YafImport::import(const string filename){
	reader = xmlNewTextReaderFilename(filename.c_str());
	if(reader == NULL){
		cerr<<"error parsing xml file"<<endl;
		return NULL;
	}
	xmlTextReaderRead(reader);
	if(loadScene()!=0){
		cerr<<"error parsing xml file"<<endl;
		xmlFreeTextReader(reader);
		return NULL;
	}

	xmlFreeTextReader(reader);
	return this->scene;
}

bool YafImport::tagEqual(const char* name){
	return (xmlStrEqual(xmlTextReaderName(reader), (const xmlChar*) name))?true:false;
}

bool YafImport::isEndTag(){
	if(xmlTextReaderNodeType(reader) == 15)
		return true;
	return false;
}

bool YafImport::isStartTag(){
	if(xmlTextReaderNodeType(reader) == 1)
		return true;
	return false;
}

string YafImport::getAttribute(const char* name){
	string s = (const char*) xmlTextReaderGetAttribute(reader, xmlCharStrdup(name));
	return s;
}

wfloat YafImport::getAttributeFloat(const char* name){
	return (wfloat)strtod(getAttribute(name).c_str(), NULL);
}


int YafImport::freeUnusedPoints(vector< pair<Point3d*, int> >& v){
	int j=0;
	for(unsigned int i=0; i<v.size();i++){
		if(v[i].second==0){
#ifdef DEBUG
			cout<<"deleting unused point:"<<*(v[i].first)<<endl;
#endif
			delete v[i].first;
		j++;
		}
	}
	return j;
}

int YafImport::initPoints(vector< pair<Point3d*, int> >& v){
	uint j=0;
	for( uint i=0; i<v.size();i++){
		if(v[i].second==1)
			scene->points.push_back(v[i].first);
		j++;
	}
	return j;
}
