#include "pch.h"
#include "CppUnitTest.h"

#include "../RRTracer/Ray.h"
#include "../RRTracer/Sphere.h"
#include "../RRTracer/RayUtilities.h"
#include "../RRTracer/Intersection.h"

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
			RRT::Sphere s(0);

			auto hits = RRTRayUtils::Intersects(s, r);

			Assert::AreEqual(hits[0].Time(), 4.0f, EPSILON);
			Assert::AreEqual(hits[1].Time(), 6.0f, EPSILON);
		}

		TEST_METHOD(Ray_Intersects_Sphere_at_Tangent)
		{
			RRT::Tuple origin = RRT::TupleFactory().Point(0.0f, 1.0f, -5.0f);
			RRT::Tuple direction = RRT::TupleFactory().Vector(0.0f, 0.0f, 1.0f);

			RRT::Ray r(origin, direction);
			RRT::Sphere s(0);

			auto hits = RRTRayUtils::Intersects(s, r);
			
			Assert::AreEqual(hits[0].Time(), 5.0f, EPSILON);
			Assert::AreEqual(hits[1].Time(), 5.0f, EPSILON);
		}

		TEST_METHOD(Ray_Misses_Sphere)
		{
			RRT::Tuple origin = RRT::TupleFactory().Point(0.0f, 1.5f, -5.0f);
			RRT::Tuple direction = RRT::TupleFactory().Vector(0.0f, 0.0f, 1.0f);

			RRT::Ray r(origin, direction);
			RRT::Sphere s(0);

			auto hits = RRTRayUtils::Intersects(s, r);
			size_t exp_count = 0;

			Assert::AreEqual(exp_count, hits.size());			
		}

		TEST_METHOD(Ray_Is_Inside_Sphere)
		{
			RRT::Tuple origin = RRT::TupleFactory().Point(0.0f, 0.0f, 0.0f);
			RRT::Tuple direction = RRT::TupleFactory().Vector(0.0f, 0.0f, 1.0f);

			RRT::Ray r(origin, direction);
			RRT::Sphere s(0);

			auto hits = RRTRayUtils::Intersects(s, r);
			
			Assert::AreEqual(hits[0].Time(), -1.0f, EPSILON);
			Assert::AreEqual(hits[1].Time(), 1.0f, EPSILON);
		}

		TEST_METHOD(Ray_Is_Behind_Sphere)
		{
			RRT::Tuple origin = RRT::TupleFactory().Point(0.0f, 0.0f, 5.0f);
			RRT::Tuple direction = RRT::TupleFactory().Vector(0.0f, 0.0f, 1.0f);

			RRT::Ray r(origin, direction);
			RRT::Sphere s(0);

			auto hits = RRTRayUtils::Intersects(s, r);
		
			Assert::AreEqual(hits[0].Time(), -6.0f, EPSILON);
			Assert::AreEqual(hits[1].Time(), -4.0f, EPSILON);
		}
	};

	TEST_CLASS(RRT_Intersection_Tests)
	{
	public:
		TEST_METHOD(Intersect_Constructor)
		{
			RRT::Sphere s(0);
			RRT::Intersection i(3.5f, s);

			Assert::AreEqual(3.5f, i.Time(), EPSILON);
			Assert::AreEqual(0, i.Object().Id());
		}

		TEST_METHOD(Intersect_Returns_List_Of_Interects_and_Objects)
		{
			RRT::Tuple origin = RRT::TupleFactory().Point(0.0f, 0.0f, -5.0f);
			RRT::Tuple direction = RRT::TupleFactory().Vector(0.0f, 0.0f, 1.0f);

			RRT::Ray r(origin, direction);
			RRT::Sphere s(1);
			std::vector<RRT::Intersection> intersect_vector = RRTRayUtils::Intersects(s, r);

			size_t exp_count = 2;

			Assert::AreEqual(exp_count, intersect_vector.size());

			Assert::AreEqual(4.0f, intersect_vector[0].Time(), EPSILON);
			Assert::AreEqual(6.0f, intersect_vector[1].Time(), EPSILON);

			Assert::AreEqual(1, intersect_vector[0].Object().Id());
			Assert::AreEqual(1, intersect_vector[0].Object().Id());
		}

		TEST_METHOD(Hit_when_all_xs_have_pos_t)
		{
			RRT::Sphere s(2);

			RRT::Intersection i1 = RRT::Intersection(1.0f, s);
			RRT::Intersection i2 = RRT::Intersection(2.0f, s);

			std::vector<RRT::Intersection> xs_vec;
			xs_vec.push_back(i1);
			xs_vec.push_back(i2);

			auto [hit, xs_obj] = RRTRayUtils::Hit(xs_vec);

			Assert::IsTrue(hit);
			Assert::AreEqual(1.0f, xs_obj.Time());
			Assert::AreEqual(2, xs_obj.Object().Id());
		}

		TEST_METHOD(Hit_when_some_have_negs_t)
		{
			RRT::Sphere s(2);

			RRT::Intersection i1 = RRT::Intersection(-1.0f, s);
			RRT::Intersection i2 = RRT::Intersection(1.0f, s);

			std::vector<RRT::Intersection> xs_vec;
			xs_vec.push_back(i1);
			xs_vec.push_back(i2);

			auto [hit, xs_obj] = RRTRayUtils::Hit(xs_vec);

			Assert::IsTrue(hit);
			Assert::AreEqual(1.0f, xs_obj.Time());
			Assert::AreEqual(2, xs_obj.Object().Id());
		}

		TEST_METHOD(Hit_when_all_have_negs_t)
		{
			RRT::Sphere s(2);

			RRT::Intersection i1 = RRT::Intersection(-1.0f, s);
			RRT::Intersection i2 = RRT::Intersection(-1.0f, s);

			std::vector<RRT::Intersection> xs_vec;
			xs_vec.push_back(i1);
			xs_vec.push_back(i2);

			auto [hit, xs_obj] = RRTRayUtils::Hit(xs_vec);

			Assert::IsFalse(hit);
			Assert::AreEqual(0, xs_obj.Object().Id());
		}

		TEST_METHOD(Hit_is_always_lowest_non_neg_t)
		{
			RRT::Sphere s(2);

			RRT::Intersection i1 = RRT::Intersection(-1.0f, s);
			RRT::Intersection i2 = RRT::Intersection(5.0f, s);
			RRT::Intersection i3 = RRT::Intersection(1.0f, s);
			RRT::Intersection i4 = RRT::Intersection(7.0f, s);
			RRT::Intersection i5 = RRT::Intersection(-3.0f, s);

			std::vector<RRT::Intersection> xs_vec;
			xs_vec.push_back(i1);
			xs_vec.push_back(i2);
			xs_vec.push_back(i3);
			xs_vec.push_back(i4);
			xs_vec.push_back(i5);

			auto [hit, xs_obj] = RRTRayUtils::Hit(xs_vec);

			Assert::IsTrue(hit);
			Assert::AreEqual(1.0f, xs_obj.Time());
			Assert::AreEqual(2, xs_obj.Object().Id());
		}
	};
}