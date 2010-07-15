#include "Matrix4x4.h"
#include <iostream>

using namespace PF;

void Matrix4x4::transform(Point3d& p) const {
	Point3d p2(p);

	Eigen::Matrix<wfloat, 4, 1> tmp;

#ifdef VEC_3D_REPRESENTED_4D
	tmp = p._point;
#else
	tmp.head<3>() = p._point;
#endif

	tmp[3] = 1.0;	// we are not operating in homogenous coordinates in the raytracer, so w should probably
					// always be set to 1 here, so that translation is not affected

	tmp = _matrix * tmp;

#ifdef VEC_3D_REPRESENTED_4D
	p._point = tmp;
#else
	p._point = tmp.head<3>();
#endif
}

void Matrix4x4::setRow(int i, wfloat a, wfloat b, wfloat c, wfloat d){
	if(i<0 || i>3){
		std::cerr<<"error setting matrix4x4, something is wrong"<<std::endl;
		return;
	}
	_matrix(i, 0)=a;
	_matrix(i, 1)=b;
	_matrix(i, 2)=c;
	_matrix(i, 3)=d;
}


Matrix4x4::Matrix4x4(int version){
	if(version == 0){
		this->null();	// maybe not necessary in constructor?
		return;
	}


	if(version == 1){	// identity matrix
		/*
		this->null();
		_matrix(0, 0)=1;
		_matrix(1, 1)=1;
		_matrix(2, 2)=1;
		_matrix(3, 3)=1;
		*/
		_matrix.setIdentity();
		return;
	}
	return;
}
void Matrix4x4::null(){
	for(int i = 0; i < 4; ++i)
		for(int j = 0; j < 4;++j)
			_matrix(i, j) = 0;

}

std::ostream& operator<<(std::ostream& str, Matrix4x4& m){
	str<<"| "<<m._matrix(0, 0)<<", "<<m._matrix(0, 1)<<", "<<m._matrix(0, 2)<<", "<<m._matrix(0, 3)<<" |"<<std::endl;
	str<<"| "<<m._matrix(1, 0)<<", "<<m._matrix(1, 1)<<", "<<m._matrix(1, 2)<<", "<<m._matrix(1, 3)<<" |"<<std::endl;
	str<<"| "<<m._matrix(2, 0)<<", "<<m._matrix(2, 1)<<", "<<m._matrix(2, 2)<<", "<<m._matrix(2, 3)<<" |"<<std::endl;
	str<<"| "<<m._matrix(3, 0)<<", "<<m._matrix(3, 1)<<", "<<m._matrix(3, 2)<<", "<<m._matrix(3, 3)<<" |";
	return str;
}
