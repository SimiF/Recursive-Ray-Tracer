#include "Matrix.h"

namespace RRT
{
	Matrix::Matrix(const size_t& r, const size_t& c, const std::vector<std::vector<float>> m)
	{
		rows = r;
		cols = c;
		matrix = m;
	}

	std::vector<float> Matrix::operator[](const int& row_index) const noexcept(false)
	{
		return matrix[row_index];
	}

	std::vector<float>& Matrix::operator[](const int& row_index) noexcept(false)
	{
		return matrix[row_index];
	}
}