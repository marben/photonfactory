#ifndef _MATRIX4X4_
#define _MATRIX4X4_

#include "config.h"
#include "Point3d.h"
#include <iostream>
#include <Eigen/Core>

namespace PF{class Matrix4x4;}

std::ostream& operator<< (std::ostream& stream, PF::Matrix4x4& m);

namespace PF{

// this matrix is for 3d transformations only. translate(Vector3d v) translates 'v' according to the matrix. etc
class Matrix4x4{
	public:
		Matrix4x4(int version=0);
		void setRow(int index, wfloat a, wfloat b, wfloat c, wfloat d);

		void transform(Point3d& point)const;
		void null();	// null matrix

		friend std::ostream& ::operator<<(std::ostream& stream, Matrix4x4& m);

	protected:

		Eigen::Matrix<wfloat, 4, 4> _matrix;
};

}	// namespace PF

#endif
