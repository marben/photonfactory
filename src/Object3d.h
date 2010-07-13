#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

#include "Point3d.h"
#include "Light.h"
#include "Ray.h"
#include <vector>
#include "Shader.h"
#include <iostream>

namespace PF{

class Object3d{
	public:
		Object3d(){shader=NULL;}
		virtual ~Object3d(){}

		virtual bool intersect(const Ray&, wfloat& t, Vector3d& normal)=0;
		void setShader(Shader* shad){shader=shad;}
		Shader* getShader(){return shader;}
		
	protected:
		Shader* shader;
};

}	// namespace PF

#endif
