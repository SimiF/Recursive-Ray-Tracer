#ifndef TRANSFORMS_H
#define TRANSFORMS_H

#include "Matrix.h"
#include "MatrixFactory.h"

namespace RRTMatrixTransforms
{
	RRT::Matrix Translation(const float& x, const float& y, const float& z);
	RRT::Matrix Scaling(const float& x, const float& y, const float& z);
	RRT::Matrix Reflection(const bool& x, const bool& y, const bool& z);
}

#endif // !TRANSFORMS_H