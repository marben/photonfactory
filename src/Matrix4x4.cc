#include "Matrix4x4.h"
#include <iostream>

using namespace PF;

void Matrix4x4::transform(Point3d& p)const{
	Point3d p2(p);
	p.x = matrix[0][0]*p2.x+matrix[0][1]*p2.y+matrix[0][2]*p2.z+matrix[0][3]*1;
	p.y = matrix[1][0]*p2.x+matrix[1][1]*p2.y+matrix[1][2]*p2.z+matrix[1][3]*1;
	p.z = matrix[2][0]*p2.x+matrix[2][1]*p2.y+matrix[2][2]*p2.z+matrix[2][3]*1;
}

void Matrix4x4::translate(Point3d& p)const{
	p.x += matrix[0][3];
	p.y += matrix[1][3];
	p.z += matrix[2][3];
}

void Matrix4x4::setRow(int i, wfloat a, wfloat b, wfloat c, wfloat d){
	if(i<0 || i>3){
		std::cerr<<"error setting matrix4x4, something is wrong"<<std::endl;
		return;
	}
	matrix[i][0]=a;
	matrix[i][1]=b;
	matrix[i][2]=c;
	matrix[i][3]=d;
}


Matrix4x4::Matrix4x4(int version){
	if(version == 0){
		this->null();	// maybe not necessary in constructor?
		return;
	}
	if(version == 1){	// jednotkova matice
		this->null();
		matrix[0][0]=1;
		matrix[1][1]=1;
		matrix[2][2]=1;
		matrix[3][3]=1;
		return;
	}
	return;
}
void Matrix4x4::null(){
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			matrix[i][j]=0;

}

std::ostream& operator<<(std::ostream& str, Matrix4x4& m){
	str<<"| "<<m.matrix[0][0]<<", "<<m.matrix[0][1]<<", "<<m.matrix[0][2]<<", "<<m.matrix[0][3]<<" |"<<std::endl;
	str<<"| "<<m.matrix[1][0]<<", "<<m.matrix[1][1]<<", "<<m.matrix[1][2]<<", "<<m.matrix[1][3]<<" |"<<std::endl;
	str<<"| "<<m.matrix[2][0]<<", "<<m.matrix[2][1]<<", "<<m.matrix[2][2]<<", "<<m.matrix[2][3]<<" |"<<std::endl;
	str<<"| "<<m.matrix[3][0]<<", "<<m.matrix[3][1]<<", "<<m.matrix[3][2]<<", "<<m.matrix[3][3]<<" |";
	return str;
}
