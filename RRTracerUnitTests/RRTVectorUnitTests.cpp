#include "pch.h"
#include "CppUnitTest.h"

#include "../RRTracer/Vector.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RRTPointUnitTests
{
	TEST_CLASS(RRTVectorUnitTests)
	{
	public:

		TEST_METHOD(VectorIsAVector)
		{
			float x{ 4.3f };
			float y{ -4.2f };
			float z{ 3.1f };
			float w{ 0.0f };
			RRT::Vector vector = RRT::Vector(4.3f, -4.2f, 3.1f);

			Assert::AreEqual(x, vector.X());
			Assert::AreEqual(y, vector.Y());
			Assert::AreEqual(z, vector.Z());
			Assert::AreEqual(w, vector.W());
		}
	};
}