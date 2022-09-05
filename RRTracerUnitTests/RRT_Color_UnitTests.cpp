#include "pch.h"
#include "CppUnitTest.h"

#include "../RRTracer/Color.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RRT_Color_UnitTests
{
	constexpr float EPSILON = 0.0001f;

	TEST_CLASS(RRT_Color_Constructor_Tests)
	{
	public:
		TEST_METHOD(Color_Constructor_Test)
		{
			RRT::Color c{ -0.5f, 0.4f, 1.7f };

			Assert::AreEqual(-0.5f, c.Red(), EPSILON);
			Assert::AreEqual(0.4f, c.Green(), EPSILON);
			Assert::AreEqual(1.7f, c.Blue(), EPSILON);
		}		
	};

	TEST_CLASS(RRT_Color_Basic_Operator_Tests)
	{
	public:
		TEST_METHOD(Adding_Colors_Should_Equal_Added_Color)
		{
			float red{ 1.6f };
			float green{ 0.7f };
			float blue{ 1.0f };

			RRT::Color c1{ 0.9f, 0.6f, 0.75f };
			RRT::Color c2{ 0.7f, 0.1f, 0.25f };

			RRT::Color added_color = c1 + c2;

			Assert::AreEqual(red, added_color.Red(), EPSILON);
			Assert::AreEqual(green, added_color.Green(), EPSILON);
			Assert::AreEqual(blue, added_color.Blue(), EPSILON);
		}

		TEST_METHOD(Subtracting_Colors_Should_Equal_Subtracted_Color)
		{
			RRT::Color c1{ 0.9f, 0.6f, 0.75f };
			RRT::Color c2{ 0.7f, 0.1f, 0.25f };

			RRT::Color subtracted_color = c1 - c2;

			Assert::AreEqual(0.2f, subtracted_color.Red(), EPSILON);
			Assert::AreEqual(0.5f, subtracted_color.Green(), EPSILON);
			Assert::AreEqual(0.5f, subtracted_color.Blue(), EPSILON);
		}

		TEST_METHOD(Multiplying_Color_By_Scalar)
		{
			RRT::Color c1{ 0.2f, 0.3f, 0.4f };			

			RRT::Color scaled_color = c1 * 2;

			Assert::AreEqual(0.4f, scaled_color.Red(), EPSILON);
			Assert::AreEqual(0.6f, scaled_color.Green(), EPSILON);
			Assert::AreEqual(0.8f, scaled_color.Blue(), EPSILON);
		}

		TEST_METHOD(Multiplying_Colors_Should_Equal_Multiplied_Color)
		{
			RRT::Color c1{ 1.0f, 0.2f, 0.4f };
			RRT::Color c2{ 0.9f, 1.0f, 0.1f };

			RRT::Color mult_color = c1 * c2;

			Assert::AreEqual(0.9f, mult_color.Red(), EPSILON);
			Assert::AreEqual(0.2f, mult_color.Green(), EPSILON);
			Assert::AreEqual(0.04f, mult_color.Blue(), EPSILON);
		}
	};
}