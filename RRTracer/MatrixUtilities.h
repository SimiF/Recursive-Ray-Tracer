#ifndef MATRIX_UTILITIES_H
#define MATRIX_UTILITIES_H

#include "Matrix.h"

namespace RRTMatrixUtils
{	
	RRT::Matrix Transpose(const RRT::Matrix& matrix);
	RRT::Matrix SubMatrix(const RRT::Matrix& matrix, const size_t& row, const size_t& col);
	RRT::Matrix Inverse(const RRT::Matrix& matrix);

	float Cofactor(const RRT::Matrix& matrix, const size_t& row, const size_t& col);
	float Minor(const RRT::Matrix& matrix, const size_t& row, const size_t& col);
	bool Invertible(const RRT::Matrix& matrix);
	float Determinant(const RRT::Matrix& matrix);	
}

#endif // !MATRIX_UTILITIES_H