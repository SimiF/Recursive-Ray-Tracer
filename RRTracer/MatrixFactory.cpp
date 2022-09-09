#include "MatrixFactory.h"

namespace RRT
{
	Matrix MatrixFactory::IdentityMatrix() const
	{
		std::vector<std::vector<float>> input{	{ 1.0f, 0.0f, 0.0f, 0.0f },
												{ 0.0f, 1.0f, 0.0f, 0.0f },
												{ 0.0f, 0.0f, 1.0f, 0.0f },
												{ 0.0f, 0.0f, 0.0f, 1.0f }};

		Matrix matrix(4, 4, input);
		return matrix;
	}
}