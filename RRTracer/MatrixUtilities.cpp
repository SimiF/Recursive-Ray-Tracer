#include "MatrixUtilities.h"

namespace RRTMatrixUtils
{
	RRT::Matrix Transpose(const RRT::Matrix& matrix)
	{
		RRT::Matrix transposed_matrix(4, 4);

		for (size_t r = 0; r < matrix.Rows(); ++r)
		{
			for (size_t c = 0; c < matrix.Cols(); ++c)
			{
				const int curr_row = (const int)r;
				const int curr_col = (const int)c;

				transposed_matrix[curr_col][curr_row] = matrix[curr_row][curr_col];
			}
		}

		return transposed_matrix;
	}

	RRT::Matrix SubMatrix(const RRT::Matrix& matrix, const size_t& row, const size_t& col)
	{
		RRT::Matrix sub_matrix(matrix.Rows() - 1, matrix.Cols() - 1);		

		for (size_t r = 0; r < matrix.Rows(); ++r)
		{
			for (size_t c = 0; c < matrix.Cols(); ++c)
			{
				const int curr_row = (const int)r;
				const int curr_col = (const int)c;

				if (curr_row != row && curr_col != col)
				{
					const float num = matrix[curr_row][curr_col];
					sub_matrix.Add(num);
				}
			}
		}

		return sub_matrix;
	}

	RRT::Matrix Inverse(const RRT::Matrix& matrix)
	{
		RRT::Matrix inv_matrix(matrix.Rows(), matrix.Cols());

		if (Invertible(matrix))
		{
			const float determinant = Determinant(matrix);

			for (size_t r = 0; r < inv_matrix.Rows(); ++r)
			{
				for (size_t c = 0; c < inv_matrix.Cols(); ++c)
				{
					const int curr_row = (const int)r;
					const int curr_col = (const int)c;

					inv_matrix[curr_col][curr_row] = Cofactor(matrix, r, c) / determinant;

					if (RRTUtils::s_floats_equal(inv_matrix[curr_col][curr_row], 0.0f))
					{
						inv_matrix[curr_col][curr_row] = 0.0f;
					}
				}
			}
		}

		return inv_matrix;
	}

	float Minor(const RRT::Matrix& matrix, const size_t& row, const size_t& col)
	{
		RRT::Matrix sub_matrix = SubMatrix(matrix, row, col);
		return Determinant(sub_matrix);
	}

	float Cofactor(const RRT::Matrix& matrix, const size_t& row, const size_t& col)
	{	
		float minor = Minor(matrix, row, col);

		size_t num = row + col;
		if (num % 2 != 0)
		{
			minor *= -1;
		}

		return minor;
	}

	float Determinant(const RRT::Matrix& matrix)
	{
		float determinant{ 0.0f };

		if (matrix.Cols() == 2 && matrix.Rows() == 2)
		{
			determinant = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
		}

		for (size_t c = 0; c < matrix.Cols(); ++c)
		{			
			const int curr_col = (const int)c;
			
			determinant += matrix[0][c] * Cofactor(matrix, 0, c);
		}

		return determinant;
	}

	bool Invertible(const RRT::Matrix& matrix)
	{
		return !RRTUtils::s_floats_equal(Determinant(matrix), 0.0f);
	}
}