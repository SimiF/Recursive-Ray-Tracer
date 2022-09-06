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

	bool operator==(const Matrix& m1, const Matrix& m2)
	{
		bool is_same{ false };

		if (m1.cols != m2.cols && m1.rows != m2.rows)
		{
			return false;
		}

		for (size_t r = 0; r < m1.rows; ++r)
		{
			for (size_t c = 0; c < m1.cols; ++c)
			{
				const int row = (const int)r;
				const int col = (const int)c;

				is_same = RRTUtils::s_floats_equal(m1[row][col], m2[row][col]);
			}
		}

		return is_same;
	}

	bool operator!=(const Matrix& m1, const Matrix& m2)
	{
		return !(m1 == m2);
	}
}