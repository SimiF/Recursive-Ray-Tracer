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
	};
}