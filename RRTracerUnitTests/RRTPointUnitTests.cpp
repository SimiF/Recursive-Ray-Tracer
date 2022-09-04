#include "pch.h"
#include "CppUnitTest.h"

#include "../RRTracer/Point.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RRTPointUnitTests
{
	TEST_CLASS(RRTPointUnitTests)
	{
	public:

		TEST_METHOD(PointIsAPoint)
		{
			float x{ 4.3f };
			float y{ -4.2f };
			float z{ 3.1f };
			float w{ 1.0f };
			RRT::Point point = RRT::Point(4.3f, -4.2f, 3.1f);

			Assert::AreEqual(x, point.X());
			Assert::AreEqual(y, point.Y());
			Assert::AreEqual(z, point.Z());
			Assert::AreEqual(w, point.W());
		}	
	};
}