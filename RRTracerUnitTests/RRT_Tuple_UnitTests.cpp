#include "pch.h"
#include "CppUnitTest.h"

#include "../RRTracer/Tuple.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RRT_Point_UnitTests
{
	TEST_CLASS(RRT_Tuple_Constructor_Tests)
	{
	public:
		TEST_METHOD(Point_is_a_Point)
		{
			float x{ 4.3f };
			float y{ -4.2f };
			float z{ 3.1f };
			float w{ 1.0f };
			RRT::Tuple point = RRT::Tuple(4.3f, -4.2f, 3.1f, 1.0f);

			Assert::AreEqual(x, point.X());
			Assert::AreEqual(y, point.Y());
			Assert::AreEqual(z, point.Z());
			Assert::AreEqual(w, point.W());
		}

		TEST_METHOD(Vector_is_a_Vector)
		{
			float x{ 4.3f };
			float y{ -4.2f };
			float z{ 3.1f };
			float w{ 0.0f };
			RRT::Tuple vector = RRT::Tuple(4.3f, -4.2f, 3.1f, 0.0f);

			Assert::AreEqual(x, vector.X());
			Assert::AreEqual(y, vector.Y());
			Assert::AreEqual(z, vector.Z());
			Assert::AreEqual(w, vector.W());
		}
	};
}