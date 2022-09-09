#ifndef TRANSFORMS_H
#define TRANSFORMS_H

#include "Matrix.h"
#include "MatrixFactory.h"

namespace RRTMatrixTransforms
{
	RRT::Matrix Translation(const float& x, const float& y, const float& z);
}

#endif // !TRANSFORMS_H