#include "pch.h"
#include "CppUnitTest.h"

#include <vector>

#include "../RRTracer/Matrix.h"
#include "../RRTracer/MatrixFactory.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RRT_Matrix_UnitTests
{	
	constexpr float EPSILON = 0.0001f;

	TEST_CLASS(RRT_Matrix_Constructor_Tests)
	{
	public:
		TEST_METHOD(Matrix_Constructor_Test)
		{
			std::vector<std::vector<float>> input_data{ { 1.0f, 2.0f, 3.0f, 4.0f }, 
														{ 5.5f, 6.5f, 7.5f, 8.5f }, 
														{ 9.0f, 10.0f, 11.0f, 12.0f },
														{ 13.5f, 14.5f, 15.5f, 16.5f } };
			RRT::Matrix test_matrix(4, 4, input_data);

			Assert::AreEqual(1.0f, test_matrix[0][0], EPSILON);
			Assert::AreEqual(4.0f, test_matrix[0][3], EPSILON);
			Assert::AreEqual(5.5f, test_matrix[1][0], EPSILON);
			Assert::AreEqual(7.5f, test_matrix[1][2], EPSILON);
			Assert::AreEqual(11.0f, test_matrix[2][2], EPSILON);
			Assert::AreEqual(13.5f, test_matrix[3][0], EPSILON);
			Assert::AreEqual(15.5f, test_matrix[3][2], EPSILON);
		}

		TEST_METHOD(Matrix_Constructor_2by2_Test)
		{
			std::vector<std::vector<float>> input_data{ { -3.0f, 5.0f},
														{ 1.0f, -2.0f } };
			RRT::Matrix test_matrix(2, 2, input_data);

			Assert::AreEqual(-3.0f, test_matrix[0][0], EPSILON);
			Assert::AreEqual(5.0f, test_matrix[0][1], EPSILON);
			Assert::AreEqual(1.0f, test_matrix[1][0], EPSILON);
			Assert::AreEqual(-2.0f, test_matrix[1][1], EPSILON);
		}

		TEST_METHOD(Matrix_Constructor_3by3_Test)
		{
			std::vector<std::vector<float>> input_data{ { -3.0f, 5.0f, 0.0f   },
														{ 1.0f, -2.0f, -7.0f   },
														{ 0.0f, 1.0f, 1.0f } };
			RRT::Matrix test_matrix(3, 3, input_data);

			Assert::AreEqual(-3.0f, test_matrix[0][0], EPSILON);
			Assert::AreEqual(-2.0f, test_matrix[1][1], EPSILON);
			Assert::AreEqual(1.0f, test_matrix[2][2], EPSILON);
		}
	};

	TEST_CLASS(RRT_Matrix_Comparison_Tests)
	{
	public:
		TEST_METHOD(Two_Matrices_Should_Equal_If_Same)
		{
			std::vector<std::vector<float>> input_data{ { 1.0f, 2.0f, 3.0f, 4.0f },
														{ 5.5f, 6.5f, 7.5f, 8.5f },
														{ 9.0f, 10.0f, 11.0f, 12.0f },
														{ 13.5f, 14.5f, 15.5f, 16.5f } };

			RRT::Matrix matrix_one(4, 4, input_data);
			RRT::Matrix matrix_two(4, 4, input_data);

			Assert::IsTrue(matrix_one == matrix_two);
			Assert::IsFalse(matrix_one != matrix_two);
		}	

		TEST_METHOD(Two_Matrices_Should_Not_Equal_If_Not_Same)
		{
			std::vector<std::vector<float>> input_data_one{ { 1.0f, 2.0f, 3.0f, 4.0f },
														{ 5.5f, 6.5f, 7.5f, 8.5f },
														{ 9.0f, 10.0f, 11.0f, 12.0f },
														{ 13.5f, 14.5f, 15.5f, 16.5f } };

			std::vector<std::vector<float>> input_data_two{ { 2.0f, 2.0f, 3.0f, 4.0f },
														{ 5.5f, 6.55f, 7.5f, 8.5f },
														{ 9.0f, 10.0f, 11.6f, 12.0f },
														{ 13.5f, 14.5f, 15.9f, -8.5f } };

			RRT::Matrix matrix_one(4, 4, input_data_one);
			RRT::Matrix matrix_two(4, 4, input_data_two);

			Assert::IsTrue(matrix_one != matrix_two);
			Assert::IsFalse(matrix_one == matrix_two);
		}
	};

	TEST_CLASS(RRT_Matrix_Multiplication_Tests)
	{
	public:
		TEST_METHOD(Multiplication_of_two_matrices)
		{
			std::vector<std::vector<float>> input_data_one{ { 1.0f, 2.0f, 3.0f, 4.0f },
															{ 5.0f, 6.0f, 7.0f, 8.0f },
															{ 9.0f, 8.0f, 7.0f, 6.0f },
															{ 5.0f, 4.0f, 3.0f, 2.0f } };

			std::vector<std::vector<float>> input_data_two{ { -2.0f, 1.0f, 2.0f, 3.0f },
															{ 3.0f, 2.0f, 1.0f, -1.0f },
															{ 4.0f, 3.0f, 6.0f, 5.0f },
															{ 1.0f, 2.0f, 7.0f, 8.0f } };

			std::vector<std::vector<float>> expected_mult{ { 20.0f, 22.0f, 50.0f, 48.0f },
															{ 44.0f, 54.0f, 114.0f, 108.0f },
															{ 48.0f, 58.0f, 110.0f, 102.0f },
															{ 16.0f, 26.0f, 46.0f, 42.0f } };

			RRT::Matrix m_one = RRT::Matrix(4, 4, input_data_one);
			RRT::Matrix m_two = RRT::Matrix(4, 4, input_data_two);
			RRT::Matrix expected_matrix = RRT::Matrix(4, 4, expected_mult);

			RRT::Matrix actual_matrix = m_one * m_two;

			Assert::IsTrue(expected_matrix == actual_matrix);
			Assert::IsFalse(expected_matrix != actual_matrix);
		}

		TEST_METHOD(Multiplication_of_matrix_and_tuple)
		{
			std::vector<std::vector<float>> input_data_one{ { 1.0f, 2.0f, 3.0f, 4.0f },
															{ 2.0f, 4.0f, 4.0f, 2.0f },
															{ 8.0f, 6.0f, 4.0f, 1.0f },
															{ 0.0f, 0.0f, 0.0f, 1.0f } };
			RRT::Matrix matrix = RRT::Matrix(4, 4, input_data_one);
			std::vector<float> tuple = { 1, 2, 3, 1 };
			std::vector<float> expected_tuple = { 18, 24, 33, 1 };

			std::vector<float> actual_tuple = matrix * tuple;			

			for (size_t i = 0; i < 4; ++i)
			{
				Assert::AreEqual(expected_tuple[i], actual_tuple[i], EPSILON);
			}
		}

		TEST_METHOD(Multiplication_of_identity_Matrix_Should_Return_Initial_matrix)
		{
			std::vector<std::vector<float>> input_data_one{ { 1.0f, 2.0f, 3.0f, 4.0f },
															{ 2.0f, 4.0f, 4.0f, 2.0f },
															{ 8.0f, 6.0f, 4.0f, 1.0f },
															{ 0.0f, 0.0f, 0.0f, 1.0f } };
			RRT::Matrix matrix = RRT::Matrix(4, 4, input_data_one);
			RRT::Matrix id_matrix = RRT::MatrixFactory().IdentityMatrix();
			RRT::Matrix new_matrix = matrix * id_matrix;

			Assert::IsTrue(matrix == new_matrix);
			Assert::IsFalse(matrix != new_matrix);
		}
	};
}