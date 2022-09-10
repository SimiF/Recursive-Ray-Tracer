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

	RRT::Matrix Rotation_X(const float& x_rad)
	{
		RRT::Matrix id_matrix = RRT::MatrixFactory().IdentityMatrix();

		id_matrix[1][1] = cosf(x_rad);
		id_matrix[1][2] = -sinf(x_rad);
		id_matrix[2][1] = sinf(x_rad);
		id_matrix[2][2] = cosf(x_rad);

		return id_matrix;
	}

	RRT::Matrix Rotation_Y(const float& x_rad)
	{
		RRT::Matrix id_matrix = RRT::MatrixFactory().IdentityMatrix();

		id_matrix[0][0] = cosf(x_rad);
		id_matrix[2][0] = -sinf(x_rad);
		id_matrix[0][2] = sinf(x_rad);
		id_matrix[2][2] = cosf(x_rad);

		return id_matrix;
	}

	RRT::Matrix Rotation_Z(const float& x_rad)
	{
		RRT::Matrix id_matrix = RRT::MatrixFactory().IdentityMatrix();

		id_matrix[0][0] = cosf(x_rad);
		id_matrix[0][1] = -sinf(x_rad);
		id_matrix[1][0] = sinf(x_rad);
		id_matrix[1][1] = cosf(x_rad);

		return id_matrix;
	}

	RRT::Matrix Shearing(const float& x_y, const float& x_z, const float& y_x, const float& y_z, const float& z_x, const float& z_y)
	{
		RRT::Matrix id_matrix = RRT::MatrixFactory().IdentityMatrix();

		

		return id_matrix;
	}
}