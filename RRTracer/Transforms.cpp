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
}