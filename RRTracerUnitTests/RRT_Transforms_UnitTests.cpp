#include "pch.h"
#include "CppUnitTest.h"

#include "../RRTracer/Tuple.h"
#include "../RRTracer/TupleFactory.h"

#include "../RRTracer/Matrix.h"
#include "../RRTracer/MatrixFactory.h"
#include "../RRTracer/MatrixUtilities.h"

#include "../RRTracer/Transforms.h"

#include <numbers>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RRT_Transforms_UnitTests
{
	constexpr float EPSILON = 0.0001f;
	constexpr float PI = 3.14159265359f;

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

		TEST_METHOD(Scaling_Transform_Vector_Test_One)
		{
			RRT::Matrix transform_matrix = RRTMatrixTransforms::Scaling(2.0f, 3.0f, 4.0f);
			RRT::Tuple vec = RRT::TupleFactory().Vector(-4.0f, 6.0f, 8.0f);
			RRT::Tuple exp_scaled_vec = RRT::TupleFactory().Vector(-8.0f, 18.0f, 32.0f);

			RRT::Tuple scaled_vec = transform_matrix * vec;

			Assert::IsTrue(exp_scaled_vec == scaled_vec);
		}

		TEST_METHOD(Scaling_Transform_Vector_Inverse_Test_One)
		{
			RRT::Matrix transform_matrix = RRTMatrixUtils::Inverse(RRTMatrixTransforms::Scaling(2.0f, 3.0f, 4.0f));
			RRT::Tuple vec = RRT::TupleFactory().Vector(-4.0f, 6.0f, 8.0f);
			RRT::Tuple exp_scaled_vec = RRT::TupleFactory().Vector(-2.0f, 2.0f, 2.0f);

			RRT::Tuple scaled_vec = transform_matrix * vec;

			Assert::IsTrue(exp_scaled_vec == scaled_vec);
		}

		TEST_METHOD(Reflecton_of_Point_Via_X_Axis)
		{
			RRT::Matrix transform_matrix = RRTMatrixTransforms::Reflection(true, false, false);
			RRT::Tuple point = RRT::TupleFactory().Point(-4.0f, 6.0f, 8.0f);
			RRT::Tuple exp_refl_point = RRT::TupleFactory().Point(4.0f, 6.0f, 8.0f);

			RRT::Tuple refl_point = transform_matrix * point;

			Assert::IsTrue(exp_refl_point == refl_point);
		}

		TEST_METHOD(Reflecton_of_Point_Via_X_Y_Axis)
		{
			RRT::Matrix transform_matrix = RRTMatrixTransforms::Reflection(true, true, false);
			RRT::Tuple point = RRT::TupleFactory().Point(-4.0f, 6.0f, 8.0f);
			RRT::Tuple exp_refl_point = RRT::TupleFactory().Point(4.0f, -6.0f, 8.0f);

			RRT::Tuple refl_point = transform_matrix * point;

			Assert::IsTrue(exp_refl_point == refl_point);
		}

		TEST_METHOD(Reflecton_of_Point_Via_X_Y_Z_Axis)
		{
			RRT::Matrix transform_matrix = RRTMatrixTransforms::Reflection(true, true, true);
			RRT::Tuple point = RRT::TupleFactory().Point(-4.0f, 6.0f, 8.0f);
			RRT::Tuple exp_refl_point = RRT::TupleFactory().Point(4.0f, -6.0f, -8.0f);

			RRT::Tuple refl_point = transform_matrix * point;

			Assert::IsTrue(exp_refl_point == refl_point);
		}

		TEST_METHOD(Rotation_Half_Quarter_Around_X_Axis)
		{
			RRT::Matrix transform_matrix = RRTMatrixTransforms::Rotation_X(PI / 4);
			RRT::Tuple point = RRT::TupleFactory().Point(0.0f, 1.0f, 0.0f);
			RRT::Tuple exp_rot_point = RRT::TupleFactory().Point(0.0f, sqrtf(2) / 2.0f, sqrtf(2) / 2.0f);

			RRT::Tuple rot_point = transform_matrix * point;

			Assert::IsTrue(exp_rot_point == rot_point);
		}

		TEST_METHOD(Rotation_Full_Quarter_Around_X_Axis)
		{
			RRT::Matrix transform_matrix = RRTMatrixTransforms::Rotation_X(PI / 2);
			RRT::Tuple point = RRT::TupleFactory().Point(0.0f, 1.0f, 0.0f);
			RRT::Tuple exp_rot_point = RRT::TupleFactory().Point(0.0f, 0.0f, 1.0f);

			RRT::Tuple rot_point = transform_matrix * point;

			Assert::IsTrue(exp_rot_point == rot_point);
		}

		TEST_METHOD(Rotation_Half_Quarter_Around_Y_Axis)
		{
			RRT::Matrix transform_matrix = RRTMatrixTransforms::Rotation_Y(PI / 4);
			RRT::Tuple point = RRT::TupleFactory().Point(0.0f, 0.0f, 1.0f);
			RRT::Tuple exp_rot_point = RRT::TupleFactory().Point(sqrtf(2) / 2.0f, 0.0f, sqrtf(2) / 2.0f);

			RRT::Tuple rot_point = transform_matrix * point;

			Assert::IsTrue(exp_rot_point == rot_point);
		}

		TEST_METHOD(Rotation_Full_Quarter_Around_Y_Axis)
		{
			RRT::Matrix transform_matrix = RRTMatrixTransforms::Rotation_Y(PI / 2);
			RRT::Tuple point = RRT::TupleFactory().Point(0.0f, 0.0f, 1.0f);
			RRT::Tuple exp_rot_point = RRT::TupleFactory().Point(1.0f, 0.0f, 0.0f);

			RRT::Tuple rot_point = transform_matrix * point;

			Assert::IsTrue(exp_rot_point == rot_point);
		}

		TEST_METHOD(Rotation_Half_Quarter_Around_Z_Axis)
		{
			RRT::Matrix transform_matrix = RRTMatrixTransforms::Rotation_Z(PI / 4);
			RRT::Tuple point = RRT::TupleFactory().Point(0.0f, 1.0f, 0.0f);
			RRT::Tuple exp_rot_point = RRT::TupleFactory().Point(-(sqrtf(2) / 2.0f), sqrtf(2) / 2.0f, 0.0f);

			RRT::Tuple rot_point = transform_matrix * point;

			Assert::IsTrue(exp_rot_point == rot_point);
		}

		TEST_METHOD(Rotation_Full_Quarter_Around_Z_Axis)
		{
			RRT::Matrix transform_matrix = RRTMatrixTransforms::Rotation_Z(PI / 2);
			RRT::Tuple point = RRT::TupleFactory().Point(0.0f, 1.0f, 0.0f);
			RRT::Tuple exp_rot_point = RRT::TupleFactory().Point(-1.0f, 0.0f, 0.0f);

			RRT::Tuple rot_point = transform_matrix * point;

			Assert::IsTrue(exp_rot_point == rot_point);
		}
	};

	TEST_CLASS(RRT_Transforms_Searing_UnitTests)
	{
	public:
		TEST_METHOD(Shearing_X_In_Proportion_To_Y)
		{
			RRT::Matrix transform_matrix = RRTMatrixTransforms::Shearing(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			RRT::Tuple point = RRT::TupleFactory().Point(2.0f, 3.0f, 4.0f);
			RRT::Tuple exp_sheared_point = RRT::TupleFactory().Point(5.0f, 3.0f, 4.0f);

			RRT::Tuple sheared_point = transform_matrix * point;

			Assert::IsTrue(exp_sheared_point == sheared_point);
		}

		TEST_METHOD(Shearing_X_In_Proportion_To_Z)
		{
			RRT::Matrix transform_matrix = RRTMatrixTransforms::Shearing(0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			RRT::Tuple point = RRT::TupleFactory().Point(2.0f, 3.0f, 4.0f);
			RRT::Tuple exp_sheared_point = RRT::TupleFactory().Point(6.0f, 3.0f, 4.0f);

			RRT::Tuple sheared_point = transform_matrix * point;

			Assert::IsTrue(exp_sheared_point == sheared_point);
		}

		TEST_METHOD(Shearing_Y_In_Proportion_To_X)
		{
			RRT::Matrix transform_matrix = RRTMatrixTransforms::Shearing(0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
			RRT::Tuple point = RRT::TupleFactory().Point(2.0f, 3.0f, 4.0f);
			RRT::Tuple exp_sheared_point = RRT::TupleFactory().Point(2.0f, 5.0f, 4.0f);

			RRT::Tuple sheared_point = transform_matrix * point;

			Assert::IsTrue(exp_sheared_point == sheared_point);
		}

		TEST_METHOD(Shearing_Y_In_Proportion_To_Z)
		{
			RRT::Matrix transform_matrix = RRTMatrixTransforms::Shearing(0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
			RRT::Tuple point = RRT::TupleFactory().Point(2.0f, 3.0f, 4.0f);
			RRT::Tuple exp_sheared_point = RRT::TupleFactory().Point(2.0f, 7.0f, 4.0f);

			RRT::Tuple sheared_point = transform_matrix * point;

			Assert::IsTrue(exp_sheared_point == sheared_point);
		}

		TEST_METHOD(Shearing_Z_In_Proportion_To_X)
		{
			RRT::Matrix transform_matrix = RRTMatrixTransforms::Shearing(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
			RRT::Tuple point = RRT::TupleFactory().Point(2.0f, 3.0f, 4.0f);
			RRT::Tuple exp_sheared_point = RRT::TupleFactory().Point(2.0f, 3.0f, 6.0f);

			RRT::Tuple sheared_point = transform_matrix * point;

			Assert::IsTrue(exp_sheared_point == sheared_point);
		}

		TEST_METHOD(Shearing_Z_In_Proportion_To_Y)
		{
			RRT::Matrix transform_matrix = RRTMatrixTransforms::Shearing(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
			RRT::Tuple point = RRT::TupleFactory().Point(2.0f, 3.0f, 4.0f);
			RRT::Tuple exp_sheared_point = RRT::TupleFactory().Point(2.0f, 3.0f, 7.0f);

			RRT::Tuple sheared_point = transform_matrix * point;

			Assert::IsTrue(exp_sheared_point == sheared_point);
		}
	};

	TEST_CLASS(RRT_ChainedTransforms_UnitTests)
	{
	public:
		TEST_METHOD(Sequence_Transformations)
		{
			RRT::Tuple point = RRT::TupleFactory().Point(1.0f, 0.0f, 1.0f);

			RRT::Matrix rot_transf = RRTMatrixTransforms::Rotation_X(PI / 2);
			RRT::Matrix scal_transf = RRTMatrixTransforms::Scaling(5.0f, 5.0f, 5.0f);
			RRT::Matrix transl_transf = RRTMatrixTransforms::Translation(10.0f, 5.0f, 7.0f);

			RRT::Tuple exp_rot_point = RRT::TupleFactory().Point(1.0f, -1.0f, 0.0f);
			RRT::Tuple exp_scal_point = RRT::TupleFactory().Point(5.0f, -5.0f, 0.0f);
			RRT::Tuple exp_transl_point = RRT::TupleFactory().Point(15.0f, 0.0f, 7.0f);

			RRT::Tuple rot_point = rot_transf * point;
			RRT::Tuple scal_point = scal_transf * rot_point;
			RRT::Tuple transl_pont = transl_transf * scal_point;

			Assert::IsTrue(rot_point == exp_rot_point);
			Assert::IsTrue(scal_point == exp_scal_point);
			Assert::IsTrue(transl_pont == exp_transl_point);
		}

		TEST_METHOD(Chained_Transforms)
		{
			RRT::Tuple point = RRT::TupleFactory().Point(1.0f, 0.0f, 1.0f);

			RRT::Matrix rot_transf = RRTMatrixTransforms::Rotation_X(PI / 2);
			RRT::Matrix scal_transf = RRTMatrixTransforms::Scaling(5.0f, 5.0f, 5.0f);
			RRT::Matrix transl_transf = RRTMatrixTransforms::Translation(10.0f, 5.0f, 7.0f);
			RRT::Matrix transf = transl_transf * scal_transf * rot_transf;

			RRT::Tuple exp_transf_point = RRT::TupleFactory().Point(15.0f, 0.0f, 7.0f);

			RRT::Tuple transf_point = transf * point;

			Assert::IsTrue(transf_point == exp_transf_point);
		}
	};
}