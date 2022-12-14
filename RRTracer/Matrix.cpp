#include "Matrix.h"

namespace RRT
{
	Matrix::Matrix(const size_t& r, const size_t& c, const std::vector<std::vector<float>> m)
	{
		rows = r;
		cols = c;
		matrix = m;
	}

	Matrix::Matrix(const size_t& r, const size_t& c)
	{
		rows = r;
		cols = c;

		matrix.resize(cols);

		for (auto& row : matrix)
		{
			row.resize(rows);
		}

		// instantiate matrix with "infinity"
		for (size_t r = 0; r < rows; ++r)
		{
			for (size_t c = 0; c < cols; ++c)
			{
				const int curr_row = (const int)r;
				const int curr_col = (const int)c;

				matrix[curr_row][curr_col] = 1e10;
			}
		}
	}

	void Matrix::Add(const float& f) noexcept(false)
	{
		for (size_t r = 0; r < rows; ++r)
		{
			for (size_t c = 0; c < cols; ++c)
			{
				const int curr_row = (const int)r;
				const int curr_col = (const int)c;

				if (RRTUtils::s_floats_equal(matrix[curr_row][curr_col], 1e10))
				{
					matrix[curr_row][curr_col] = f;
					return;
				}
			}
		}
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
				
				if (!is_same)
				{
					return false;
				}
			}
		}

		return is_same;
	}

	bool operator!=(const Matrix& m1, const Matrix& m2)
	{
		return !(m1 == m2);
	}

	Matrix Matrix::operator*(const Matrix& m) const
	{
		Matrix resulting_matrix(m.Rows(), m.Cols());

		for (size_t r = 0; r < m.rows; ++r)
		{
			for (size_t c = 0; c < m.cols; ++c)
			{
				const int row = (const int)r;
				const int col = (const int)c;				

				resulting_matrix[row][col] = matrix[row][0] * m[0][c] +
					matrix[row][1] * m[1][col] +
					matrix[row][2] * m[2][col] +
					matrix[row][3] * m[3][col];
			}
		}

		return resulting_matrix;
	}

	std::vector<float> Matrix::operator*(const std::vector<float>& v) const
	{
		std::vector<float> resulting_tuple;
		resulting_tuple.resize(4);

		for (size_t i = 0; i < 4; ++i)
		{
			std::vector<float> row = matrix[i];		

			resulting_tuple[i] = row[0] * v[0] + row[1] * v[1] + row[2] * v[2] + row[3] * v[3];
		}

		return resulting_tuple;
	}	

	Tuple Matrix::operator*(const Tuple& t) const
	{		
		std::vector<float> resulting_tuple;
		resulting_tuple.resize(4);

		for (size_t i = 0; i < 4; ++i)
		{
			std::vector<float> row = matrix[i];

			resulting_tuple[i] = row[0] * t.X() + row[1] * t.Y() + row[2] * t.Z() + row[3] * t.W();
		}

		return { resulting_tuple[0], resulting_tuple[1], resulting_tuple[2], resulting_tuple[3] };
	}
}