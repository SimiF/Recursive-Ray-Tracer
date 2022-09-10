#include "pch.h"
#include "CppUnitTest.h"

#include "../RRTracer/Tuple.h"
#include "../RRTracer/TupleFactory.h"

#include "../RRTracer/Matrix.h"
#include "../RRTracer/MatrixFactory.h"
#include "../RRTracer/MatrixUtilities.h"

#include "../RRTracer/Transforms.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RRT_Transforms_UnitTests
{
	constexpr float EPSILON = 0.0001f;

	TEST_CLASS(RRT_Transforms_Tests)
	{
	public:
		TEST_METHOD(Linear_Transform_Test_One)
		{
			RRT::Matrix transform_matrix = RRTMatrixTransforms::Translation(5.0f, -3.0f, 2.0f);
			RRT::Tuple point = RRT::TupleFactory().Point(-3.0f, 4.0f, 5.0f);
			RRT::Tuple exp_translated_point = RRT::TupleFactory().Point(2.0f, 1.0f, 7.0f);

			RRT::Tuple translated_point = transform_matrix * point;

			Assert::IsTrue(exp_translated_point == translated_point);
		}

		TEST_METHOD(Linear_Transform_Inverse_Test_One)
		{
			RRT::Matrix transform_matrix = RRTMatrixUtils::Inverse(RRTMatrixTransforms::Translation(5.0f, -3.0f, 2.0f));
			RRT::Tuple point = RRT::TupleFactory().Point(-3.0f, 4.0f, 5.0f);
			RRT::Tuple exp_translated_point = RRT::TupleFactory().Point(-8.0f, 7.0f, 3.0f);

			RRT::Tuple translated_point = transform_matrix * point;

			Assert::IsTrue(exp_translated_point == translated_point);
		}

		TEST_METHOD(Linear_Transform_Vector_Not_Affected)
		{
			RRT::Matrix transform_matrix = RRTMatrixTransforms::Translation(5.0f, -3.0f, 2.0f);
			RRT::Tuple vec = RRT::TupleFactory().Vector(-3.0f, 4.0f, 5.0f);
			RRT::Tuple exp_vec = RRT::TupleFactory().Vector(-3.0f, 4.0f, 5.0f);

			RRT::Tuple transl_vec = transform_matrix * vec;

			Assert::IsTrue(exp_vec == transl_vec);
		}

		TEST_METHOD(Scaling_Transform_Point_Test_One)
		{
			RRT::Matrix transform_matrix = RRTMatrixTransforms::Scaling(2.0f, 3.0f, 4.0f);
			RRT::Tuple point = RRT::TupleFactory().Point(-4.0f, 6.0f, 8.0f);
			RRT::Tuple exp_scaled_point = RRT::TupleFactory().Point(-8.0f, 18.0f, 32.0f);

			RRT::Tuple scaled_point = transform_matrix * point;

			Assert::IsTrue(exp_scaled_point == scaled_point);
		}
	};
}