#include "pch.h"
#include "CppUnitTest.h"

#include "../RRTracer/Ray.h"
#include "../RRTracer/Sphere.h"
#include "../RRTracer/RayUtilities.h"

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

	TEST_CLASS(RRT_Ray_Functional_Tests)
	{
	public:
		TEST_METHOD(RRT_Ray_Position_Test)
		{
			RRT::Tuple origin = RRT::TupleFactory().Point(2.0f, 3.0f, 4.0f);
			RRT::Tuple direction = RRT::TupleFactory().Vector(1.0f, 0.0f, 0.0f);
			RRT::Ray ray(origin, direction);

			RRT::Tuple exp_pt_one = RRT::TupleFactory().Point(2.0f, 3.0f, 4.0f);
			RRT::Tuple exp_pt_two = RRT::TupleFactory().Point(3.0f, 3.0f, 4.0f);
			RRT::Tuple exp_pt_three = RRT::TupleFactory().Point(1.0f, 3.0f, 4.0f);
			RRT::Tuple exp_pt_four = RRT::TupleFactory().Point(4.5f, 3.0f, 4.0f);

			RRT::Tuple act_pt_one = ray.Position(0.0f);
			RRT::Tuple act_pt_two = ray.Position(1.0f);
			RRT::Tuple act_pt_three = ray.Position(-1.0f);
			RRT::Tuple act_pt_four = ray.Position(2.5f);

			Assert::IsTrue(exp_pt_one == act_pt_one);
			Assert::IsTrue(exp_pt_two == act_pt_two);
			Assert::IsTrue(exp_pt_three == act_pt_three);
			Assert::IsTrue(exp_pt_four == act_pt_four);
		}

		TEST_METHOD(Ray_Intersects_Sphere)
		{
			RRT::Tuple origin = RRT::TupleFactory().Point(0.0f, 0.0f, -5.0f);
			RRT::Tuple direction = RRT::TupleFactory().Vector(0.0f, 0.0f, 1.0f);
			
			RRT::Ray r(origin, direction);
			RRT::Sphere s;

			auto [hit, xs] = RRTRayUtils::Intersects(s, r);

			Assert::IsTrue(hit);
			Assert::AreEqual(xs[0], 4.0f, EPSILON);
			Assert::AreEqual(xs[1], 6.0f, EPSILON);
		}
	};
}