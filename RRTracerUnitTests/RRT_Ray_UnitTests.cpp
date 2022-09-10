#include "pch.h"
#include "CppUnitTest.h"

#include "../RRTracer/Ray.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RRT_Ray_UnitTests
{
	constexpr float EPSILON = 0.0001f;

	TEST_CLASS(RRT_Ray_Constructor_Tests)
	{
	public:
		TEST_METHOD(Color_Constructor_Test)
		{
			RRT::Tuple origin = RRT::TupleFactory().Point(1.0f, 2.0f, 3.0f);
			RRT::Tuple direction = RRT::TupleFactory().Vector(4.0f, 5.0f, 6.0f);
			RRT::Ray ray(origin, direction);
			
			Assert::IsTrue(ray.Origin() == origin);
			Assert::IsTrue(ray.Direction() == direction);
		}
	};	
}