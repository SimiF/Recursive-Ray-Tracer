#include "pch.h"
#include "CppUnitTest.h"

#include <vector>

#include "../RRTracer/Matrix.h"

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

			Assert::AreEqual(1.0f, test_matrix[0,0], EPSILON);
			Assert::AreEqual(4.0f, test_matrix[0,3], EPSILON);
			Assert::AreEqual(5.5f, test_matrix[1,0], EPSILON);
			Assert::AreEqual(7.5f, test_matrix[1,2], EPSILON);
			Assert::AreEqual(11.0f, test_matrix[2,2], EPSILON);
			Assert::AreEqual(13.5f, test_matrix[3,0], EPSILON);
			Assert::AreEqual(15.5f, test_matrix[3,2], EPSILON);
		}
	};
}