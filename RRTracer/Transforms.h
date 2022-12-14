#ifndef TRANSFORMS_H
#define TRANSFORMS_H

#include "Matrix.h"
#include "MatrixFactory.h"

#include <cmath>

namespace RRTMatrixTransforms
{
	RRT::Matrix Translation(const float& x, const float& y, const float& z);
	RRT::Matrix Scaling(const float& x, const float& y, const float& z);
	RRT::Matrix Reflection(const bool& x, const bool& y, const bool& z);

	RRT::Matrix Rotation_X(const float& x_rad);
	RRT::Matrix Rotation_Y(const float& x_rad);
	RRT::Matrix Rotation_Z(const float& x_rad);

	RRT::Matrix Shearing(const float& x_y, const float& x_z, const float& y_x, const float& y_z, const float& z_x, const float& z_y);
}

#endif // !TRANSFORMS_H