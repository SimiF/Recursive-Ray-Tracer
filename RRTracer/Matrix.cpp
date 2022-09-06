#include "Matrix.h"

namespace RRT
{
	Matrix::Matrix(const size_t& r, const size_t& c, const std::vector<std::vector<float>> m)
	{
		rows = r;
		cols = c;
		matrix = m;
	}
}