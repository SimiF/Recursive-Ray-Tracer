#include "pch.h"
#include "CppUnitTest.h"

#include "../RRTracer/TupleFactory.hpp"
#include "../RRTracer/Tuple.hpp"

#include "../RRTracer/TupleUtilities.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RRT_Point_UnitTests
{
	constexpr float EPSILON = 0.0001f;

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

			Assert::AreEqual(x, point.X(), EPSILON);
			Assert::AreEqual(y, point.Y(), EPSILON);
			Assert::AreEqual(z, point.Z(), EPSILON);
			Assert::IsTrue(point.IsPoint());
		}

		TEST_METHOD(Vector_is_a_Vector)
		{
			float x{ 4.3f };
			float y{ -4.2f };
			float z{ 3.1f };
			float w{ 0.0f };

			RRT::Tuple vector = RRT::Tuple(4.3f, -4.2f, 3.1f, 0.0f);			

			Assert::AreEqual(x, vector.X(), EPSILON);
			Assert::AreEqual(y, vector.Y(), EPSILON);
			Assert::AreEqual(z, vector.Z(), EPSILON);
			Assert::IsTrue(vector.IsVector());
		}
	};

	TEST_CLASS(RRT_TupleFactory_Constructor_Tests)
	{
	public:
		TEST_METHOD(Factory_Point_is_a_Point)
		{
			float x{ 4.3f };
			float y{ -4.2f };
			float z{ 3.1f };		

			RRT::Tuple point = RRT::TupleFactory().Point(4.3f, -4.2f, 3.1f);

			Assert::AreEqual(x, point.X(), EPSILON);
			Assert::AreEqual(y, point.Y(), EPSILON);
			Assert::AreEqual(z, point.Z(), EPSILON);
			Assert::IsTrue(point.IsPoint());
		}

		TEST_METHOD(Factory_Vector_is_a_Vector)
		{
			float x{ 4.3f };
			float y{ -4.2f };
			float z{ 3.1f };			

			RRT::Tuple vector = RRT::TupleFactory().Vector(4.3f, -4.2f, 3.1f);

			Assert::AreEqual(x, vector.X(), EPSILON);
			Assert::AreEqual(y, vector.Y(), EPSILON);
			Assert::AreEqual(z, vector.Z(), EPSILON);
			Assert::IsTrue(vector.IsVector());
		}
	};

	TEST_CLASS(RRT_Tuple_Basic_Operator_Tests)
	{
	public:
		TEST_METHOD(Addition_Of_Two_Tuples)
		{
			float x{ 1.0f };
			float y{ 1.0f };
			float z{ 6.0f };

			RRT::Tuple tuple_one{ 3.0f, -2.0f, 5.0f, 1.0f }; // point
			RRT::Tuple tuple_two{ -2.0f, 3.0f, 1.0f, 0.0f }; // vector

			RRT::Tuple resulting_tuple = tuple_one + tuple_two;

			Assert::AreEqual(x, resulting_tuple.X(), EPSILON);
			Assert::AreEqual(y, resulting_tuple.Y(), EPSILON);
			Assert::AreEqual(z, resulting_tuple.Z(), EPSILON);
			Assert::IsTrue(resulting_tuple.IsPoint()); // point + vector = point
		}

		TEST_METHOD(Subtraction_of_two_points_should_be_Vector)
		{
			float x{ -2.0f };
			float y{ -4.0f };
			float z{ -6.0f };

			RRT::Tuple point_one = RRT::TupleFactory().Point(3.0f, 2.0f, 1.0f);
			RRT::Tuple point_two = RRT::TupleFactory().Point(5.0f, 6.0f, 7.0f);

			RRT::Tuple resulting_vector = point_one - point_two;

			Assert::AreEqual(x, resulting_vector.X(), EPSILON);
			Assert::AreEqual(y, resulting_vector.Y(), EPSILON);
			Assert::AreEqual(z, resulting_vector.Z(), EPSILON);
			Assert::IsTrue(resulting_vector.IsVector());
		}

		TEST_METHOD(Subtraction_of_vector_from_point_should_result_in_point)
		{
			float x{ -2.0f };
			float y{ -4.0f };
			float z{ -6.0f };

			RRT::Tuple point_one = RRT::TupleFactory().Point(3.0f, 2.0f, 1.0f);
			RRT::Tuple vector_one = RRT::TupleFactory().Vector(5.0f, 6.0f, 7.0f);

			RRT::Tuple resulting_point = point_one - vector_one;

			Assert::AreEqual(x, resulting_point.X(), EPSILON);
			Assert::AreEqual(y, resulting_point.Y(), EPSILON);
			Assert::AreEqual(z, resulting_point.Z(), EPSILON);
			Assert::IsTrue(resulting_point.IsPoint());
		}

		TEST_METHOD(Addition_of_vector_to_point_should_result_in_point)
		{
			float x{ 8.0f };
			float y{ 8.0f };
			float z{ 8.0f };

			RRT::Tuple point_one = RRT::TupleFactory().Point(3.0f, 2.0f, 1.0f);
			RRT::Tuple vector_one = RRT::TupleFactory().Vector(5.0f, 6.0f, 7.0f);

			RRT::Tuple resulting_point = point_one + vector_one;

			Assert::AreEqual(x, resulting_point.X(), EPSILON);
			Assert::AreEqual(y, resulting_point.Y(), EPSILON);
			Assert::AreEqual(z, resulting_point.Z(), EPSILON);
			Assert::IsTrue(resulting_point.IsPoint());
		}

		TEST_METHOD(Addition_of_vector_to_vector_should_result_in_vector)
		{
			float x{ 8.0f };
			float y{ 8.0f };
			float z{ 8.0f };

			RRT::Tuple vector_one = RRT::TupleFactory().Vector(3.0f, 2.0f, 1.0f);
			RRT::Tuple vector_two = RRT::TupleFactory().Vector(5.0f, 6.0f, 7.0f);

			RRT::Tuple resulting_vector = vector_one + vector_two;

			Assert::AreEqual(x, resulting_vector.X(), EPSILON);
			Assert::AreEqual(y, resulting_vector.Y(), EPSILON);
			Assert::AreEqual(z, resulting_vector.Z(), EPSILON);
			Assert::IsTrue(resulting_vector.IsVector());
		}

		TEST_METHOD(Subtraction_of_vector_from_vector_should_result_in_vector)
		{
			float x{ -2.0f };
			float y{ -4.0f };
			float z{ -6.0f };

			RRT::Tuple vector_one = RRT::TupleFactory().Vector(3.0f, 2.0f, 1.0f);
			RRT::Tuple vector_two = RRT::TupleFactory().Vector(5.0f, 6.0f, 7.0f);

			RRT::Tuple resulting_vector = vector_one - vector_two;

			Assert::AreEqual(x, resulting_vector.X(), EPSILON);
			Assert::AreEqual(y, resulting_vector.Y(), EPSILON);
			Assert::AreEqual(z, resulting_vector.Z(), EPSILON);
			Assert::IsTrue(resulting_vector.IsVector());
		}

		TEST_METHOD(Negation_of_tuple)
		{
			float x{ -2.0f };
			float y{ -4.0f };
			float z{ -6.0f };

			RRT::Tuple tuple_one{ 2.0f, 4.0f, 6.0f, 0.0f };
			RRT::Tuple tuple_two = -tuple_one;

			Assert::AreEqual(x, tuple_two.X(), EPSILON);
			Assert::AreEqual(y, tuple_two.Y(), EPSILON);
			Assert::AreEqual(z, tuple_two.Z(), EPSILON);
			Assert::IsTrue(tuple_two.IsVector());
		}

		TEST_METHOD(Scalar_multiplication_of_vector_should_result_In_vector)
		{
			float x{ -2.0f };
			float y{ -4.0f };
			float z{ -6.0f };

			RRT::Tuple vector_one = RRT::TupleFactory().Vector(-1.0f, -2.0f, -3.0f);
			RRT::Tuple vector_two = vector_one * 2;

			Assert::AreEqual(x, vector_two.X(), EPSILON);
			Assert::AreEqual(y, vector_two.Y(), EPSILON);
			Assert::AreEqual(z, vector_two.Z(), EPSILON);
			Assert::IsTrue(vector_two.IsVector());
		}

		TEST_METHOD(Decimal_Scalar_multiplication_of_vector_should_result_In_vector)
		{
			float x{ -2.0f };
			float y{ -4.0f };
			float z{ -6.0f };

			RRT::Tuple vector_one = RRT::TupleFactory().Vector(-4.0f, -8.0f, -12.0f);
			RRT::Tuple vector_two = vector_one * 0.5;

			Assert::AreEqual(x, vector_two.X(), EPSILON);
			Assert::AreEqual(y, vector_two.Y(), EPSILON);
			Assert::AreEqual(z, vector_two.Z(), EPSILON);
			Assert::IsTrue(vector_two.IsVector());
		}

		TEST_METHOD(Scalar_division_of_vector_should_result_In_vector)
		{
			float x{ -2.0f };
			float y{ -4.0f };
			float z{ -6.0f };

			RRT::Tuple vector_one = RRT::TupleFactory().Vector(-4.0f, -8.0f, -12.0f);
			RRT::Tuple vector_two = vector_one / 2;

			Assert::AreEqual(x, vector_two.X(), EPSILON);
			Assert::AreEqual(y, vector_two.Y(), EPSILON);
			Assert::AreEqual(z, vector_two.Z(), EPSILON);
			Assert::IsTrue(vector_two.IsVector());
		}

		TEST_METHOD(Magnitude_Of_100_Vector_Should_be_1)
		{
			float expected_magnitude{ 1.0f };
			RRT::Tuple vector = RRT::TupleFactory().Vector(1.0f, 0.0f, 0.0f);

			Assert::AreEqual(expected_magnitude, vector.magnitude(), EPSILON);
		}

		TEST_METHOD(Magnitude_Of_010_Vector_Should_be_1)
		{
			float expected_magnitude{ 1.0f };
			RRT::Tuple vector = RRT::TupleFactory().Vector(0.0f, 1.0f, 0.0f);

			Assert::AreEqual(expected_magnitude, vector.magnitude(), EPSILON);
		}

		TEST_METHOD(Magnitude_Of_001_Vector_Should_be_1)
		{
			float expected_magnitude{ 1.0f };
			RRT::Tuple vector = RRT::TupleFactory().Vector(0.0f, 0.0f, 1.0f);

			Assert::AreEqual(expected_magnitude, vector.magnitude(), EPSILON);
		}

		TEST_METHOD(Magnitude_Of_123_Vector_Should_be_sqrt14)
		{
			float expected_magnitude{ sqrtf(14.0f)};
			RRT::Tuple vector = RRT::TupleFactory().Vector(1.0f, 2.0f, 3.0f);

			Assert::AreEqual(expected_magnitude, vector.magnitude(), EPSILON);
		}	

		TEST_METHOD(Magnitude_Of_neg123_Vector_Should_be_sqrt14)
		{
			float expected_magnitude{ sqrtf(14.0f) };
			RRT::Tuple vector = RRT::TupleFactory().Vector(-1.0f, -2.0f, -3.0f);

			Assert::AreEqual(expected_magnitude, vector.magnitude(), EPSILON);
		}

		TEST_METHOD(Normalizing_Vector_400_gives_100)
		{
			RRT::Tuple expected_vector = RRT::TupleFactory().Vector(1.0f, 0.0f, 0.0f);
			RRT::Tuple vector = RRT::TupleFactory().Vector(4.0f, 0.0f, 0.0f);
			
			RRT::Tuple normalized_vector = RRTTupleUtils::Normalize(vector);

			Assert::AreEqual(expected_vector.X(), normalized_vector.X(), EPSILON);
			Assert::AreEqual(expected_vector.Y(), normalized_vector.Y(), EPSILON);
			Assert::AreEqual(expected_vector.Z(), normalized_vector.Z(), EPSILON);
		}

		TEST_METHOD(Normalizing_Vector_has_1_mag)
		{			
			RRT::Tuple vector = RRT::TupleFactory().Vector(15.2f, -2.3f, 29.30f);

			RRT::Tuple normalized_vector = RRTTupleUtils::Normalize(vector);

			Assert::AreEqual(1.0f, normalized_vector.magnitude(), EPSILON);
		}

		TEST_METHOD(Dot_product_should_be_20)
		{
			float expected_dot = 20.0f;
			RRT::Tuple vector_one = RRT::TupleFactory().Vector(1.0f, 2.0f, 3.0f);
			RRT::Tuple vector_two = RRT::TupleFactory().Vector(2.0f, 3.0f, 4.0f);

			float actual_dot = RRTTupleUtils::Dot(vector_one, vector_two);

			Assert::AreEqual(expected_dot, actual_dot, EPSILON);
		}

		TEST_METHOD(Cross_product_should_equal_expected_one)
		{
			float x{ -1.0f };
			float y{ 2.0f };
			float z{ -1.0f };

			RRT::Tuple vector_one = RRT::TupleFactory().Vector(1.0f, 2.0f, 3.0f);
			RRT::Tuple vector_two = RRT::TupleFactory().Vector(2.0f, 3.0f, 4.0f);

			RRT::Tuple cross_vector = RRTTupleUtils::Cross(vector_one, vector_two);

			Assert::AreEqual(x, cross_vector.X(), EPSILON);
			Assert::AreEqual(y, cross_vector.Y(), EPSILON);
			Assert::AreEqual(z, cross_vector.Z(), EPSILON);
			Assert::IsTrue(cross_vector.IsVector());
		}

		TEST_METHOD(Cross_product_should_equal_expected_two)
		{
			float x{ 1.0f };
			float y{ -2.0f };
			float z{ 1.0f };

			RRT::Tuple vector_one = RRT::TupleFactory().Vector(1.0f, 2.0f, 3.0f);
			RRT::Tuple vector_two = RRT::TupleFactory().Vector(2.0f, 3.0f, 4.0f);

			RRT::Tuple cross_vector = RRTTupleUtils::Cross(vector_two, vector_one);

			Assert::AreEqual(x, cross_vector.X(), EPSILON);
			Assert::AreEqual(y, cross_vector.Y(), EPSILON);
			Assert::AreEqual(z, cross_vector.Z(), EPSILON);
			Assert::IsTrue(cross_vector.IsVector());
		}
	};
}