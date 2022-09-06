#include "MatrixUtilities.h"

namespace RRTMatrixUtils
{
	RRT::Matrix Transpose(const RRT::Matrix& matrix)
	{
		RRT::Matrix transposed_matrix(4, 4);

		std::vector<float> row_one = matrix[0];
		std::vector<float> row_two = matrix[1];
		std::vector<float> row_three = matrix[2];
		std::vector<float> row_four = matrix[3];

		for (size_t c = 0; c < matrix.Cols(); ++c)
		{
			const int col = (const int)c;

			transposed_matrix[0][col] = row_one[col];
			transposed_matrix[1][col] = row_two[col];
			transposed_matrix[2][col] = row_three[col];
			transposed_matrix[3][col] = row_four[col];
		}

		return transposed_matrix;
	}
}