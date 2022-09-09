#include "pch.h"
#include "CppUnitTest.h"

#include <vector>

#include "../RRTracer/Matrix.h"
#include "../RRTracer/MatrixFactory.h"
#include "../RRTracer/MatrixUtilities.h"

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
															{ 40.0f, 58.0f, 110.0f, 102.0f },
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

		TEST_METHOD(Multiplication_of_Tuple_Should_Return_Initial_matrix)
		{
			std::vector<float> tuple = { 18, 24, 33, 1 };
			std::vector<float> expected_tuple = { 18, 24, 33, 1 };

			RRT::Matrix id_matrix = RRT::MatrixFactory().IdentityMatrix();
			std::vector<float> actual_tuple = id_matrix * tuple;

			for (size_t i = 0; i < 4; ++i)
			{
				Assert::AreEqual(expected_tuple[i], actual_tuple[i], EPSILON);
			}
		}

		TEST_METHOD(Transpose_of_ID_Matrix_Should_Return_ID_Matrix)
		{
			RRT::Matrix id_mat_one = RRT::MatrixFactory().IdentityMatrix();
			RRT::Matrix id_mat_two = RRTMatrixUtils::Transpose(id_mat_one);

			Assert::IsTrue(id_mat_one == id_mat_two);
			Assert::IsFalse(id_mat_one != id_mat_two);
		}

		TEST_METHOD(Transpose_Matrix_Should_Return_Transposed_Matrix)
		{
			std::vector<std::vector<float>> input_data_one{ { 0.0f, 9.0f, 3.0f, 0.0f },
															{ 9.0f, 8.0f, 0.0f, 8.0f },
															{ 1.0f, 8.0f, 5.0f, 3.0f },
															{ 0.0f, 0.0f, 5.0f, 8.0f } };

			std::vector<std::vector<float>> input_data_two{ { 0.0f, 9.0f, 1.0f, 0.0f },
															{ 9.0f, 8.0f, 8.0f, 0.0f },
															{ 3.0f, 0.0f, 5.0f, 5.0f },
															{ 0.0f, 8.0f, 3.0f, 8.0f } };

			RRT::Matrix original_matrix = RRT::Matrix(4, 4, input_data_one);
			RRT::Matrix expected_matrix = RRT::Matrix(4, 4, input_data_two);

			RRT::Matrix actual_matrix = RRTMatrixUtils::Transpose(original_matrix);

			Assert::IsTrue(expected_matrix == actual_matrix);
			Assert::IsFalse(expected_matrix != actual_matrix);
		}

		TEST_METHOD(Transpose_Matrix_Twice_Return_Original_Matrix)
		{
			std::vector<std::vector<float>> input_data_one{ { 0.0f, 9.0f, 3.0f, 0.0f },
															{ 9.0f, 8.0f, 0.0f, 8.0f },
															{ 1.0f, 8.0f, 5.0f, 3.0f },
															{ 0.0f, 0.0f, 5.0f, 8.0f } };			

			RRT::Matrix expected_matrix = RRT::Matrix(4, 4, input_data_one);
			RRT::Matrix actual_matrix = RRT::Matrix(4, 4, input_data_one);
			actual_matrix = RRTMatrixUtils::Transpose(actual_matrix);
			actual_matrix = RRTMatrixUtils::Transpose(actual_matrix);			

			Assert::IsTrue(expected_matrix == actual_matrix);
			Assert::IsFalse(expected_matrix != actual_matrix);
		}

		TEST_METHOD(Determinant_of_2d_matrix_is_right_matrix)
		{
			std::vector<std::vector<float>> input_data{ { 1.0f, 5.0f },
														{ -3.0f, 2.0f } };

			RRT::Matrix matrix = RRT::Matrix(2, 2, input_data);
			float exp_det = 17.0f;

			Assert::AreEqual(exp_det, RRTMatrixUtils::Determinant(matrix), EPSILON);
		}

		TEST_METHOD(Submatrix_of_3_by_3_is_proper_matrix)
		{
			std::vector<std::vector<float>> input_data{ { 1.0f, 5.0f, 0.0f },
														{ -3.0f, 2.0f, 7.0f },
														{ 0.0f, 6.0f, -3.0f } };

			std::vector<std::vector<float>> exp_data{	{ -3.0f, 2.0f },
														{ 0.0f, 6.0f } };

			RRT::Matrix matrix = RRT::Matrix(3, 3, input_data);
			RRT::Matrix exp_submat = RRT::Matrix(2, 2, exp_data);

			RRT::Matrix act_submat = RRTMatrixUtils::SubMatrix(matrix, 0, 2);

			Assert::IsTrue(exp_submat == act_submat);
			Assert::IsFalse(exp_submat != act_submat);
		}

		TEST_METHOD(Submatrix_of_4_by_4_is_proper_matrix)
		{
			std::vector<std::vector<float>> input_data{ { -6.0f, 1.0f, 1.0f, 6.0f },
														{ -8.0f, 5.0f, 8.0f, 6.0f },
														{ -1.0f, 0.0f, 8.0f, 2.0f },
														{ -7.0f, 1.0f, -1.0f, 1.0f } };

			std::vector<std::vector<float>> exp_data{ { -6.0f, 1.0f, 6.0f },
														{ -8.0f, 8.0f, 6.0f },
														{ -7.0f, -1.0f, 1.0f } };

			RRT::Matrix matrix = RRT::Matrix(4, 4, input_data);
			RRT::Matrix exp_submat = RRT::Matrix(3, 3, exp_data);

			RRT::Matrix act_submat = RRTMatrixUtils::SubMatrix(matrix, 2, 1);

			Assert::IsTrue(exp_submat == act_submat);
			Assert::IsFalse(exp_submat != act_submat);
		}

		TEST_METHOD(Minor_of_3_by_3_matrix)
		{			
			std::vector<std::vector<float>> input_data{ { 3.0, 5.0f, 0.0f },
														{ 2.0f, -1.0f, -7.0f },
														{ 6.0, -1.0f, 5.0f } };
			
			float exp_minor = 25.0f;

			RRT::Matrix matrix = RRT::Matrix(3, 3, input_data);	
			RRT::Matrix sub_matrix = RRTMatrixUtils::SubMatrix(matrix, 1, 0);
			float determinant = RRTMatrixUtils::Determinant(sub_matrix);

			float minor = RRTMatrixUtils::Minor(matrix, 1, 0);

			Assert::AreEqual(exp_minor, determinant, EPSILON);
			Assert::AreEqual(exp_minor, minor, EPSILON);
		}

		TEST_METHOD(Cofactor_of_3_by_3_matrix)
		{
			std::vector<std::vector<float>> input_data{ { 3.0, 5.0f, 0.0f },
														{ 2.0f, -1.0f, -7.0f },
														{ 6.0, -1.0f, 5.0f } };

			RRT::Matrix matrix = RRT::Matrix(3, 3, input_data);

			float exp_minor_one = -12.0f;
			float exp_cofactor_one = -12.0f;
			float exp_minor_two = 25.0f;
			float exp_cofactor_two = -25.0;

			float act_minor_one = RRTMatrixUtils::Minor(matrix, 0, 0);
			float act_cofactor_one = RRTMatrixUtils::Cofactor(matrix, 0, 0);
			float act_minor_two = RRTMatrixUtils::Minor(matrix, 1, 0);
			float act_cofactor_two = RRTMatrixUtils::Cofactor(matrix, 1, 0);

			Assert::AreEqual(exp_minor_one, act_minor_one, EPSILON);
			Assert::AreEqual(exp_cofactor_one, act_cofactor_one, EPSILON);
			Assert::AreEqual(exp_minor_two, act_minor_two, EPSILON);
			Assert::AreEqual(exp_cofactor_two, act_cofactor_two, EPSILON);
		}

		TEST_METHOD(Determinant_of_3_by_3_matrix)
		{
			std::vector<std::vector<float>> input_data{ { 1.0, 2.0f, 6.0f },
														{ -5.0f, 8.0f, -4.0f },
														{ 2.0, 6.0f, 4.0f } };

			RRT::Matrix matrix = RRT::Matrix(3, 3, input_data);

			float exp_cofactor_one = 56.0f;
			float exp_cofactor_two = 12.0f;
			float exp_cofactor_three = -46.0f;
			float exp_determinant = -196.0;

			float act_cofactor_one = RRTMatrixUtils::Cofactor(matrix, 0, 0);
			float act_cofactor_two = RRTMatrixUtils::Cofactor(matrix, 0, 1);
			float act_cofactor_three = RRTMatrixUtils::Cofactor(matrix, 0, 2);
			float act_determinant = RRTMatrixUtils::Determinant(matrix);

			Assert::AreEqual(exp_cofactor_one, act_cofactor_one, EPSILON);
			Assert::AreEqual(exp_cofactor_two, act_cofactor_two, EPSILON);
			Assert::AreEqual(exp_cofactor_three, act_cofactor_three, EPSILON);
			Assert::AreEqual(exp_determinant, act_determinant, EPSILON);
		}

		TEST_METHOD(Determinant_of_4_by_4_matrix)
		{
			std::vector<std::vector<float>> input_data{ { -2.0, -8.0f, 3.0f, 5.0f },
														{ -3.0f, 1.0f, 7.0f, 3.0f },
														{ 1.0f, 2.0f, -9.0f, 6.0f },
														{ -6.0f, 7.0f, 7.0f, -9.0f } };

			RRT::Matrix matrix = RRT::Matrix(4, 4, input_data);

			float exp_cofactor_one = 690.0f;
			float exp_cofactor_two = 447.0f;
			float exp_cofactor_three = 210.0f;
			float exp_cofactor_four = 51.0f;
			float exp_determinant = -4071.0f;

			float act_cofactor_one = RRTMatrixUtils::Cofactor(matrix, 0, 0);
			float act_cofactor_two = RRTMatrixUtils::Cofactor(matrix, 0, 1);
			float act_cofactor_three = RRTMatrixUtils::Cofactor(matrix, 0, 2);
			float act_cofactor_four = RRTMatrixUtils::Cofactor(matrix, 0, 3);
			float act_determinant = RRTMatrixUtils::Determinant(matrix);

			Assert::AreEqual(exp_cofactor_one, act_cofactor_one, EPSILON);
			Assert::AreEqual(exp_cofactor_two, act_cofactor_two, EPSILON);
			Assert::AreEqual(exp_cofactor_three, act_cofactor_three, EPSILON);
			Assert::AreEqual(exp_cofactor_four, act_cofactor_four, EPSILON);
			Assert::AreEqual(exp_determinant, act_determinant, EPSILON);
		}

		TEST_METHOD(Invertible_4_by_4_matrix_true)
		{
			std::vector<std::vector<float>> input_data{ { 6.0, 4.0f, 4.0f, 4.0f },
														{ 5.0f, 5.0f, 7.0f, 6.0f },
														{ 4.0f, -9.0f, 3.0f, -7.0f },
														{ 9.0f, 1.0f, 7.0f, -6.0f } };
			
			RRT::Matrix matrix = RRT::Matrix(4, 4, input_data);
			float exp_det = -2120.0f;

			Assert::AreEqual(exp_det, RRTMatrixUtils::Determinant(matrix), EPSILON);
			Assert::IsTrue(RRTMatrixUtils::Invertible(matrix));			
		}

		TEST_METHOD(Invertible_4_by_4_matrix_false)
		{
			std::vector<std::vector<float>> input_data{ { -4.0, 2.0f, -2.0f, -3.0f },
														{ 9.0f, 6.0f, 2.0f, 6.0f },
														{ 0.0f, -5.0f, 1.0f, -5.0f },
														{ 0.0f, 0.0f, 0.0f, 0.0f } };

			RRT::Matrix matrix = RRT::Matrix(4, 4, input_data);
			float exp_det = 0.0f;

			Assert::AreEqual(exp_det, RRTMatrixUtils::Determinant(matrix), EPSILON);
			Assert::IsFalse(RRTMatrixUtils::Invertible(matrix));			
		}

		TEST_METHOD(Calculation_of_Inverse_Matrix_One)
		{
			std::vector<std::vector<float>> input_data{ { -5.0, 2.0f, 6.0f, -8.0f },
														{ 1.0f, -5.0f, 1.0f, 8.0f },
														{ 7.0f, 7.0f, -6.0f, -7.0f },
														{ 1.0f, -3.0f, 7.0f, 4.0f } };

			std::vector<std::vector<float>> inverse_data{	{ 0.21805f, 0.45113f, 0.24060f, -0.04511f },
															{ -0.80827f, -1.45677f, -0.44361f, 0.52068f },
															{ -0.07895f, -0.22368f, -0.05263f, 0.19737f },
															{ -0.52256f, -0.81391f, -0.30075f, 0.30639f } };

			float exp_determ_one = 532.0f;
			float exp_cofactor_one = -160.0f;
			float exp_cofactor_two = 105.0f;

			float exp_3_2 = -(160.0f / 532.0f);
			float exp_2_3 = (105.0f / 532.0f);

			RRT::Matrix matrix(4, 4, input_data);
			RRT::Matrix exp_inv_matrix(4, 4, inverse_data);

			RRT::Matrix act_inv_matrix = RRTMatrixUtils::Inverse(matrix);

			Assert::AreEqual(exp_determ_one, RRTMatrixUtils::Determinant(matrix), EPSILON);
			Assert::AreEqual(exp_cofactor_one, RRTMatrixUtils::Cofactor(matrix, 2, 3), EPSILON);
			Assert::AreEqual(exp_cofactor_two, RRTMatrixUtils::Cofactor(matrix, 3, 2), EPSILON);

			Assert::AreEqual(exp_3_2, act_inv_matrix[3][2], EPSILON);
			Assert::AreEqual(exp_2_3, act_inv_matrix[2][3], EPSILON);
			
			Assert::IsTrue(exp_inv_matrix == act_inv_matrix);
			Assert::IsFalse(exp_inv_matrix != act_inv_matrix);
		}

		TEST_METHOD(Calculation_of_Inverse_Matrix_Two)
		{
			std::vector<std::vector<float>> input_data{ { 9.0, 3.0f, 0.0f, 9.0f },
														{ -5.0f, -2.0f, -6.0f, -3.0f },
														{ -4.0f, 9.0f, 6.0f, 4.0f },
														{ -7.0f, 6.0f, 6.0f, 2.0f } };

			std::vector<std::vector<float>> inverse_data{ { -0.04074f, -0.07778f, 0.14444f, -0.22222f },
															{ -0.07778f, 0.03333f, 0.36667f, -0.33333f },
															{ -0.02901f, -0.14630f, -0.10926f, 0.12963f },
															{ 0.17778f, 0.06667f, -0.26667f, 0.33333f } };			

			RRT::Matrix matrix(4, 4, input_data);
			RRT::Matrix exp_inv_matrix(4, 4, inverse_data);

			RRT::Matrix act_inv_matrix = RRTMatrixUtils::Inverse(matrix);

			Assert::IsTrue(exp_inv_matrix == act_inv_matrix);
			Assert::IsFalse(exp_inv_matrix != act_inv_matrix);
		}

		TEST_METHOD(Calculation_of_Inverse_Matrix_Three)
		{
			std::vector<std::vector<float>> input_data{ { 8.0, -5.0f, 9.0f, 2.0f },
														{ 7.0f, 5.0f, 6.0f, 1.0f },
														{ -6.0f, 0.0f, 9.0f, 6.0f },
														{ -3.0f, 0.0f, -9.0f, -4.0f } };

			std::vector<std::vector<float>> inverse_data{ { -0.15385f, -0.15385f, -0.28205f, -0.53846f },
															{ -0.07692f, 0.12308f, 0.02564f, 0.03077f },
															{ 0.35897f, 0.35897f, 0.43590f, 0.92308f },
															{ -0.69231f, -0.69231f, -0.76923f, -1.92308f } };

			RRT::Matrix matrix(4, 4, input_data);
			RRT::Matrix exp_inv_matrix(4, 4, inverse_data);

			RRT::Matrix act_inv_matrix = RRTMatrixUtils::Inverse(matrix);

			Assert::IsTrue(exp_inv_matrix == act_inv_matrix);
			Assert::IsFalse(exp_inv_matrix != act_inv_matrix);
		}

		TEST_METHOD(Theorem_of_Inversion_of_Matrices_test)
		{
			std::vector<std::vector<float>> input_data_one{ { 8.0, -5.0f, 9.0f, 2.0f },
														{ 7.0f, 5.0f, 6.0f, 1.0f },
														{ -6.0f, 0.0f, 9.0f, 6.0f },
														{ -3.0f, 0.0f, -9.0f, -4.0f } };

			std::vector<std::vector<float>> input_data_two{ { 9.0, 3.0f, 0.0f, 9.0f },
														{ -5.0f, -2.0f, -6.0f, -3.0f },
														{ -4.0f, 9.0f, 6.0f, 4.0f },
														{ -7.0f, 6.0f, 6.0f, 2.0f } };

			RRT::Matrix matrix_one(4, 4, input_data_one);
			RRT::Matrix matrix_two(4, 4, input_data_two);

			RRT::Matrix mult_matrix_one = matrix_one * matrix_two;
			RRT::Matrix mult_matrix_two = matrix_two * matrix_one;

			Assert::IsTrue(matrix_one == (mult_matrix_one * RRTMatrixUtils::Inverse(matrix_two)));
			Assert::IsTrue(matrix_two == (mult_matrix_two * RRTMatrixUtils::Inverse(matrix_one)));
		}

		TEST_METHOD(Identity_Matrix_Inversed_Is_Identity_Matrix)
		{
			RRT::Matrix identity_matrix = RRT::MatrixFactory().IdentityMatrix();

			Assert::IsTrue(identity_matrix == RRTMatrixUtils::Inverse(identity_matrix));
		}

		TEST_METHOD(Matrix_Times_Inversed_Matrix_Is_Identity_Matrix)
		{
			std::vector<std::vector<float>> input_data_one{ { 8.0, -5.0f, 9.0f, 2.0f },
														{ 7.0f, 5.0f, 6.0f, 1.0f },
														{ -6.0f, 0.0f, 9.0f, 6.0f },
														{ -3.0f, 0.0f, -9.0f, -4.0f } };

			RRT::Matrix matrix_one(4, 4, input_data_one);
			RRT::Matrix identity_matrix = RRT::MatrixFactory().IdentityMatrix();

			Assert::IsTrue(matrix_one * RRTMatrixUtils::Inverse(matrix_one) == identity_matrix);
		}

		TEST_METHOD(Inverse_of_Transpose_Is_Equal_To_Transpose_Of_Inverse)
		{
			std::vector<std::vector<float>> input_data_one{ { 8.0, -5.0f, 9.0f, 2.0f },
														{ 7.0f, 5.0f, 6.0f, 1.0f },
														{ -6.0f, 0.0f, 9.0f, 6.0f },
														{ -3.0f, 0.0f, -9.0f, -4.0f } };

			RRT::Matrix matrix_one(4, 4, input_data_one);

			RRT::Matrix transposed_inverse = RRTMatrixUtils::Inverse(RRTMatrixUtils::Transpose(matrix_one));
			RRT::Matrix inversed_transpose = RRTMatrixUtils::Transpose(RRTMatrixUtils::Inverse(matrix_one));

			Assert::IsTrue(transposed_inverse == inversed_transpose);
		}
	};
}