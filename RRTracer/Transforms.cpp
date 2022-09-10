#include "Transforms.h"

namespace RRTMatrixTransforms
{
	RRT::Matrix Translation(const float& x, const float& y, const float& z)
	{
		RRT::Matrix id_matrix = RRT::MatrixFactory().IdentityMatrix();

		id_matrix[0][3] = x;
		id_matrix[1][3] = y;
		id_matrix[2][3] = z;

		return id_matrix;
	}

	RRT::Matrix Scaling(const float& x, const float& y, const float& z)
	{
		RRT::Matrix id_matrix = RRT::MatrixFactory().IdentityMatrix();

		id_matrix[0][0] = x;
		id_matrix[1][1] = y;
		id_matrix[2][2] = z;

		return id_matrix;
	}	

	RRT::Matrix Reflection(const bool& x, const bool& y, const bool& z)
	{
		float xf = 1.0f;
		float yf = 1.0f;
		float zf = 1.0f;

		if (x) { xf = -1.0f; }
		if (y) { yf = -1.0f; }
		if (z) { zf = -1.0f; }

		return Scaling(xf, yf, zf);
	}
}