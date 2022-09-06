#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

namespace RRT
{
	class Matrix
	{
	public:
		Matrix() = default;
		Matrix(const size_t& r, const size_t& c, const std::vector<std::vector<float>> m);

		std::vector<float> operator[](const int& row_index) const noexcept(false);
		std::vector<float>& operator[](const int& row_index) noexcept(false);

	private:
		std::vector<std::vector<float>> matrix;
		size_t rows = 0;
		size_t cols = 0;
	};
}

#endif // !MATRIX_H