#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include "Utilities.h"

namespace RRT
{
	class Matrix
	{
	public:
		Matrix() = default;
		Matrix(const size_t& r, const size_t& c);
		Matrix(const size_t& r, const size_t& c, const std::vector<std::vector<float>> m);

		inline size_t Rows() const { return rows; }
		inline size_t Cols() const { return cols;  }

		std::vector<float> operator[](const int& row_index) const noexcept(false);
		std::vector<float>& operator[](const int& row_index) noexcept(false);

		friend bool operator==(const Matrix& m1, const Matrix& m2);
		friend bool operator!=(const Matrix& m1, const Matrix& m2);

		Matrix operator*(const Matrix& m) const;
		std::vector<float> operator*(const std::vector<float>& v) const;

		void Transpose() noexcept(false);

	private:
		std::vector<std::vector<float>> matrix;
		size_t rows = 0;
		size_t cols = 0;
	};
}

#endif // !MATRIX_H