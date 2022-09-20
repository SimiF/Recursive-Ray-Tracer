#include "pch.h"
#include "CppUnitTest.h"

#include <optional>

#include "../RRTracer/Ray.h"
#include "../RRTracer/Transforms.h"
#include "../RRTracer/Sphere.h"
#include "../RRTracer/RayUtilities.h"
#include "../RRTracer/Intersection.h"
#include "../RRTracer/PointLight.h"
#include "../RRTracer/Material.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RRT_Ray_UnitTests
{
	constexpr float EPSILON = 0.0001f;

	TEST_CLASS(RRT_Ray_Constructor_Tests)
	{
	public:
		TEST_METHOD(Ray_Constructor_Test)
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

			std::optional<RRT::Intersection> result = RRTRayUtils::Hit(xs_vec);

			Assert::IsTrue(result.has_value());
			Assert::AreEqual(1.0f, result->Time());
			Assert::AreEqual(2, result->Object().Id());
		}

		TEST_METHOD(Hit_when_some_have_negs_t)
		{
			RRT::Sphere s(2);

			RRT::Intersection i1 = RRT::Intersection(-1.0f, s);
			RRT::Intersection i2 = RRT::Intersection(1.0f, s);

			std::vector<RRT::Intersection> xs_vec;
			xs_vec.push_back(i1);
			xs_vec.push_back(i2);

			std::optional<RRT::Intersection> result = RRTRayUtils::Hit(xs_vec);

			Assert::IsTrue(result.has_value());
			Assert::AreEqual(1.0f, result->Time());
			Assert::AreEqual(2, result->Object().Id());
		}

		TEST_METHOD(Hit_when_all_have_negs_t)
		{
			RRT::Sphere s(2);

			RRT::Intersection i1 = RRT::Intersection(-1.0f, s);
			RRT::Intersection i2 = RRT::Intersection(-1.0f, s);

			std::vector<RRT::Intersection> xs_vec;
			xs_vec.push_back(i1);
			xs_vec.push_back(i2);

			std::optional<RRT::Intersection> result = RRTRayUtils::Hit(xs_vec);

			Assert::IsFalse(result.has_value());			
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

			std::optional<RRT::Intersection> result = RRTRayUtils::Hit(xs_vec);

			Assert::IsTrue(result.has_value());
			Assert::AreEqual(1.0f, result->Time());
			Assert::AreEqual(2, result->Object().Id());
		}

		TEST_METHOD(Translating_a_ray)
		{
			RRT::Tuple ray_origin = RRT::TupleFactory().Point(1.0f, 2.0f, 3.0f);
			RRT::Tuple ray_direction = RRT::TupleFactory().Vector(0.0f, 1.0f, 0.0f);
			RRT::Ray ray(ray_origin, ray_direction);

			RRT::Matrix translation_matrix = RRTMatrixTransforms::Translation(3.0f, 4.0f, 5.0f);
			RRT::Ray transformed_ray = RRTRayUtils::Transform(ray, translation_matrix);

			RRT::Tuple exp_point = RRT::TupleFactory().Point(4.0f, 6.0f, 8.0f);
			RRT::Tuple exp_dir = RRT::TupleFactory().Vector(0.0f, 1.0f, 0.0f);

			Assert::IsTrue(exp_point == transformed_ray.Origin());
			Assert::IsTrue(exp_dir == transformed_ray.Direction());
		}

		TEST_METHOD(Scaling_a_ray)
		{
			RRT::Tuple ray_origin = RRT::TupleFactory().Point(1.0f, 2.0f, 3.0f);
			RRT::Tuple ray_direction = RRT::TupleFactory().Vector(0.0f, 1.0f, 0.0f);
			RRT::Ray ray(ray_origin, ray_direction);

			RRT::Matrix scaling_matrix = RRTMatrixTransforms::Scaling(2.0f, 3.0f, 4.0f);
			RRT::Ray transformed_ray = RRTRayUtils::Transform(ray, scaling_matrix);

			RRT::Tuple exp_point = RRT::TupleFactory().Point(2.0f, 6.0f, 12.0f);
			RRT::Tuple exp_dir = RRT::TupleFactory().Vector(0.0f, 3.0f, 0.0f);

			Assert::IsTrue(exp_point == transformed_ray.Origin());
			Assert::IsTrue(exp_dir == transformed_ray.Direction());
		}

		TEST_METHOD(Initial_Sphere_Transform_is_Normal_matrix)
		{
			RRT::Sphere s = RRT::Sphere(0);
			RRT::Matrix exp_matrix = RRT::MatrixFactory().IdentityMatrix();

			Assert::IsTrue(exp_matrix == s.Transform());
		}

		TEST_METHOD(Able_to_change_Sphere_transform)
		{
			RRT::Sphere s = RRT::Sphere(0);
			RRT::Matrix translation_matrix = RRTMatrixTransforms::Translation(2.0f, 3.0f, 4.0f);
			s.Transform(translation_matrix);

			RRT::Matrix exp_matrix = RRTMatrixTransforms::Translation(2.0f, 3.0f, 4.0f);

			Assert::IsTrue(exp_matrix == s.Transform());
		}

		TEST_METHOD(Intersect_Func_Automatically_USes_Transform_Method)
		{
			RRT::Tuple ray_origin = RRT::TupleFactory().Point(0.0f, 0.0f, -5.0f);
			RRT::Tuple ray_direction = RRT::TupleFactory().Vector(0.0f, 0.0f, 1.0f);
			RRT::Ray ray(ray_origin, ray_direction);
			RRT::Sphere s = RRT::Sphere(0);
			RRT::Matrix scaling_matrix = RRTMatrixTransforms::Scaling(2.0f, 2.0f, 2.0f);
			s.Transform(scaling_matrix);

			std::vector<RRT::Intersection> xs_points = RRTRayUtils::Intersects(s, ray);

			size_t exp_count = 2;
			
			Assert::AreEqual(exp_count, xs_points.size());
			Assert::AreEqual(3.0f, xs_points[0].Time(), EPSILON);
			Assert::AreEqual(7.0f, xs_points[1].Time(), EPSILON);
		}

		TEST_METHOD(Intersect_Func_Automatically_USes_Transform_Method_Translated_Matrix)
		{
			RRT::Tuple ray_origin = RRT::TupleFactory().Point(0.0f, 0.0f, -5.0f);
			RRT::Tuple ray_direction = RRT::TupleFactory().Vector(0.0f, 0.0f, 1.0f);
			RRT::Ray ray(ray_origin, ray_direction);
			RRT::Sphere s = RRT::Sphere(0);
			RRT::Matrix translating_matrix = RRTMatrixTransforms::Translation(5.0f, 0.0f, 0.0f);
			s.Transform(translating_matrix);

			std::vector<RRT::Intersection> xs_points = RRTRayUtils::Intersects(s, ray);

			size_t exp_count = 0;

			Assert::AreEqual(exp_count, xs_points.size());			
		}		
	};

	TEST_CLASS(RRT_Normal_Vector_Tests)
	{
	public:
		TEST_METHOD(Normal_Vector_Test_One)
		{
			RRT::Sphere s(0);
			
			RRT::Tuple normal_vec = RRTRayUtils::Normal_At(s, RRT::TupleFactory().Point(1.0f, 0.0f, 0.0f));

			RRT::Tuple exp_normal_vec = RRT::TupleFactory().Vector(1.0f, 0.0f, 0.0f);

			Assert::IsTrue(exp_normal_vec == normal_vec);
		}

		TEST_METHOD(Normal_Vector_Test_Two)
		{
			RRT::Sphere s(0);

			RRT::Tuple normal_vec = RRTRayUtils::Normal_At(s, RRT::TupleFactory().Point(0.0f, 1.0f, 0.0f));

			RRT::Tuple exp_normal_vec = RRT::TupleFactory().Vector(0.0f, 1.0f, 0.0f);

			Assert::IsTrue(exp_normal_vec == normal_vec);
		}

		TEST_METHOD(Normal_Vector_Test_Three)
		{
			RRT::Sphere s(0);

			RRT::Tuple normal_vec = RRTRayUtils::Normal_At(s, RRT::TupleFactory().Point(0.0f, 0.0f, 1.0f));

			RRT::Tuple exp_normal_vec = RRT::TupleFactory().Vector(0.0f, 0.0f, 1.0f);

			Assert::IsTrue(exp_normal_vec == normal_vec);
		}

		TEST_METHOD(Normal_Vector_Test_Four)
		{
			RRT::Sphere s(0);

			float ind_point = sqrtf(3.0f) / 3.0f;
			RRT::Tuple normal_vec = RRTRayUtils::Normal_At(s, RRT::TupleFactory().Point(ind_point, ind_point, ind_point));

			RRT::Tuple exp_normal_vec = RRT::TupleFactory().Vector(ind_point, ind_point, ind_point);

			Assert::IsTrue(exp_normal_vec == normal_vec);
		}

		TEST_METHOD(Normal_Vector_Test_Translated_Sphere)
		{
			RRT::Sphere s(0);
			s.Transform(RRTMatrixTransforms::Translation(0.0f, 1.0f, 0.0f));			
			RRT::Tuple normal_vec = RRTRayUtils::Normal_At(s, RRT::TupleFactory().Point(0.0f, 1.70711f, -0.70711f));

			RRT::Tuple exp_normal_vec = RRT::TupleFactory().Vector(0.0f, 0.70711f, -0.70711f);

			Assert::IsTrue(exp_normal_vec == normal_vec);
		}

		TEST_METHOD(Normal_Vector_Test_Transformed_Sphere)
		{
			RRT::Sphere s(0);
			RRT::Matrix transform = RRTMatrixTransforms::Scaling(1.0f, 0.5f, 1.0f) * RRTMatrixTransforms::Rotation_Z(3.14159265f / 5.0f);
			s.Transform(transform);
			RRT::Tuple normal_vec = RRTRayUtils::Normal_At(s, RRT::TupleFactory().Point(0.0f, sqrtf(2.0f) / 2.0f, -sqrtf(2.0f) / 2.0f));

			RRT::Tuple exp_normal_vec = RRT::TupleFactory().Vector(0.0f, 0.97014f, -0.24254f);

			Assert::IsTrue(exp_normal_vec == normal_vec);
		}
	};

	TEST_CLASS(RRT_Reflection_Vector_Tests)
	{
	public:
		TEST_METHOD(Reflecting_Vector_Approaching_At_45_deg)
		{
			RRT::Tuple in_vec = RRT::TupleFactory().Vector(1.0f, -1.0f, 0.0f);
			RRT::Tuple norm_vec = RRT::TupleFactory().Vector(0.0f, 1.0f, 0.0f);
			RRT::Tuple exp_refl_vec = RRT::TupleFactory().Vector(1.0f, 1.0f, 0.0f);

			RRT::Tuple act_refl_vec = RRTRayUtils::Reflect(in_vec, norm_vec);

			Assert::IsTrue(exp_refl_vec == act_refl_vec);
		}	

		TEST_METHOD(Reflecting_Vector_Approaching_At_Slanted_Surface)
		{
			RRT::Tuple in_vec = RRT::TupleFactory().Vector(0.0f, -1.0f, 0.0f);
			float ind_num = sqrtf(2.0f) / 2.0f;
			RRT::Tuple norm_vec = RRT::TupleFactory().Vector(ind_num, ind_num, 0.0f);
			RRT::Tuple exp_refl_vec = RRT::TupleFactory().Vector(1.0f, 0.0f, 0.0f);

			RRT::Tuple act_refl_vec = RRTRayUtils::Reflect(in_vec, norm_vec);

			Assert::IsTrue(exp_refl_vec == act_refl_vec);
		}
	};

	TEST_CLASS(RRT_Point_Light_Tests)
	{
	public:
		TEST_METHOD(Point_Light_Creation_Test)
		{
			RRT::Color intensity = { 1.0f, 1.0f, 1.0f };
			RRT::Tuple position = RRT::TupleFactory().Point(0.0f, 0.0f, 0.0f);
			RRT::PointLight pl = RRT::PointLight(intensity, position);

			Assert::IsTrue(position == pl.Position());

			Assert::AreEqual(intensity.Red(), pl.Intensity().Red(), EPSILON);
			Assert::AreEqual(intensity.Blue(), pl.Intensity().Blue(), EPSILON);
			Assert::AreEqual(intensity.Green(), pl.Intensity().Green(), EPSILON);
		}	
	};

	TEST_CLASS(RRT_Material_Tests)
	{
	public:
		TEST_METHOD(Material_Default_Creation)
		{
			RRT::Material m = RRT::Material();
			
			Assert::AreEqual(1.0f, m.Color().Red(), EPSILON);
			Assert::AreEqual(1.0f, m.Color().Blue(), EPSILON);
			Assert::AreEqual(1.0f, m.Color().Green(), EPSILON);

			Assert::AreEqual(0.1f, m.Ambient(), EPSILON);
			Assert::AreEqual(0.9f, m.Diffuse(), EPSILON);
			Assert::AreEqual(0.9f, m.Specular(), EPSILON);
			Assert::AreEqual(200.0f, m.Shininess(), EPSILON);
		}

		TEST_METHOD(Sphere_has_default_material)
		{
			RRT::Sphere s(1);
			RRT::Material def_material = RRT::Material();

			Assert::AreEqual(s.Material().Color().Red(), def_material.Color().Red(), EPSILON);
			Assert::AreEqual(s.Material().Color().Blue(), def_material.Color().Blue(), EPSILON);
			Assert::AreEqual(s.Material().Color().Green(), def_material.Color().Green(), EPSILON);

			Assert::AreEqual(s.Material().Ambient(), def_material.Ambient(), EPSILON);
			Assert::AreEqual(s.Material().Diffuse(), def_material.Diffuse(), EPSILON);
			Assert::AreEqual(s.Material().Specular(), def_material.Specular(), EPSILON);
			Assert::AreEqual(s.Material().Shininess(), def_material.Shininess(), EPSILON);
		}

		TEST_METHOD(Can_Change_Sphere_Material)
		{
			RRT::Sphere s(1);
			RRT::Material def_material = RRT::Material();
			def_material.Ambient(1.0f);
			s.Material() = def_material;

			Assert::AreEqual(s.Material().Color().Red(), def_material.Color().Red(), EPSILON);
			Assert::AreEqual(s.Material().Color().Blue(), def_material.Color().Blue(), EPSILON);
			Assert::AreEqual(s.Material().Color().Green(), def_material.Color().Green(), EPSILON);

			Assert::AreEqual(s.Material().Ambient(), def_material.Ambient(), EPSILON);
			Assert::AreEqual(s.Material().Diffuse(), def_material.Diffuse(), EPSILON);
			Assert::AreEqual(s.Material().Specular(), def_material.Specular(), EPSILON);
			Assert::AreEqual(s.Material().Shininess(), def_material.Shininess(), EPSILON);
		}
	};

	TEST_CLASS(RRT_Light_Tests)
	{
	public:
		TEST_METHOD(Eye_Is_Between_Light_And_Surface)
		{
			RRT::Material mat = RRT::Material();
			RRT::Tuple pos = RRT::TupleFactory().Point(0.0f, 0.0f, 0.0f);

			RRT::Tuple eye_vec = RRT::TupleFactory().Vector(0.0f, 0.0f, -1.0f);
			RRT::Tuple normal_vec = RRT::TupleFactory().Vector(0.0f, 0.0f, -1.0f);
			RRT::PointLight light = RRT::PointLight({ 1.0f, 1.0f, 1.0f }, RRT::TupleFactory().Point(0.0f, 0.0f, -1.0f));

			RRT::Color exp_color = RRT::Color(1.9f, 1.9f, 1.9f);
			RRT::Color act_color = RRTRayUtils::Lighting(mat, pos, light, eye_vec, normal_vec);

			Assert::IsTrue(exp_color == act_color);
		}

		TEST_METHOD(Eye_Is_45_deg_Above_Light)
		{
			RRT::Material mat = RRT::Material();
			RRT::Tuple pos = RRT::TupleFactory().Point(0.0f, 0.0f, 0.0f);

			float ind_point = sqrtf(2.0f) / 2.0f;

			RRT::Tuple eye_vec = RRT::TupleFactory().Vector(0.0f, ind_point, -ind_point);
			RRT::Tuple normal_vec = RRT::TupleFactory().Vector(0.0f, 0.0f, -1.0f);
			RRT::PointLight light = RRT::PointLight({ 1.0f, 1.0f, 1.0f }, RRT::TupleFactory().Point(0.0f, 0.0f, -1.0f));

			RRT::Color exp_color = RRT::Color(1.0f, 1.0f, 1.0f);
			RRT::Color act_color = RRTRayUtils::Lighting(mat, pos, light, eye_vec, normal_vec);

			Assert::IsTrue(exp_color == act_color);
		}

		TEST_METHOD(Light_Is_45_deg_Above_Eye)
		{
			RRT::Material mat = RRT::Material();
			RRT::Tuple pos = RRT::TupleFactory().Point(0.0f, 0.0f, 0.0f);			

			RRT::Tuple eye_vec = RRT::TupleFactory().Vector(0.0f, 0.0f, -1.0f);
			RRT::Tuple normal_vec = RRT::TupleFactory().Vector(0.0f, 0.0f, -1.0f);
			RRT::PointLight light = RRT::PointLight({ 1.0f, 1.0f, 1.0f }, RRT::TupleFactory().Point(0.0f, 10.0f, -10.0f));

			RRT::Color exp_color = RRT::Color(0.7364f, 0.7364f, 0.7364f);
			RRT::Color act_color = RRTRayUtils::Lighting(mat, pos, light, eye_vec, normal_vec);

			Assert::IsTrue(exp_color == act_color);
		}

		TEST_METHOD(Light_Is_90_deg_Above_Eye)
		{
			RRT::Material mat = RRT::Material();
			RRT::Tuple pos = RRT::TupleFactory().Point(0.0f, 0.0f, 0.0f);

			float ind_point = sqrtf(2.0f) / 2.0f;

			RRT::Tuple eye_vec = RRT::TupleFactory().Vector(0.0f, -ind_point, -ind_point);
			RRT::Tuple normal_vec = RRT::TupleFactory().Vector(0.0f, 0.0f, -1.0f);
			RRT::PointLight light = RRT::PointLight({ 1.0f, 1.0f, 1.0f }, RRT::TupleFactory().Point(0.0f, 10.0f, -10.0f));

			RRT::Color exp_color = RRT::Color(1.6364f, 1.6364f, 1.6364f);
			RRT::Color act_color = RRTRayUtils::Lighting(mat, pos, light, eye_vec, normal_vec);

			Assert::AreEqual(exp_color.Red(), act_color.Red(), EPSILON);
			Assert::AreEqual(exp_color.Green(), act_color.Green(), EPSILON);
			Assert::AreEqual(exp_color.Blue(), act_color.Blue(), EPSILON);
		}

		TEST_METHOD(Light_Is_Behind_Surface)
		{
			RRT::Material mat = RRT::Material();
			RRT::Tuple pos = RRT::TupleFactory().Point(0.0f, 0.0f, 0.0f);			

			RRT::Tuple eye_vec = RRT::TupleFactory().Vector(0.0f, 0.0f, -1.0);
			RRT::Tuple normal_vec = RRT::TupleFactory().Vector(0.0f, 0.0f, -1.0f);
			RRT::PointLight light = RRT::PointLight({ 1.0f, 1.0f, 1.0f }, RRT::TupleFactory().Point(0.0f, 0.0f, 10.0f));

			RRT::Color exp_color = RRT::Color(0.1f, 0.1f, 0.1f);
			RRT::Color act_color = RRTRayUtils::Lighting(mat, pos, light, eye_vec, normal_vec);

			Assert::IsTrue(exp_color == act_color);
		}
	};
}