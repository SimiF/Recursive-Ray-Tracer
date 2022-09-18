#include "RayUtilities.h"

namespace RRTRayUtils
{
	std::vector<RRT::Intersection> Intersects(const RRT::Sphere& sphere, const RRT::Ray& ray)
	{
		RRT::Ray transformed_ray = Transform(ray, RRTMatrixUtils::Inverse(sphere.Transform()));

		bool hit_flag = false;
		std::vector<RRT::Intersection> xs_points(0);

		RRT::Tuple sphere_to_ray = transformed_ray.Origin() - RRT::TupleFactory().Point(0.0f, 0.0f, 0.0f);
		float a = RRTTupleUtils::Dot(transformed_ray.Direction(), transformed_ray.Direction());
		float b = 2 * RRTTupleUtils::Dot(transformed_ray.Direction(), sphere_to_ray);
		float c = RRTTupleUtils::Dot(sphere_to_ray, sphere_to_ray) - 1;
		float discriminant = b * b - (4 * a * c);

		if (discriminant >= 0)
		{
			hit_flag = true;

			float t1 = (-b - sqrtf(discriminant)) / (2 * a);
			float t2 = (-b + sqrtf(discriminant)) / (2 * a);

			if (t1 <= t2)
			{
				xs_points.push_back(RRT::Intersection(t1, sphere));
				xs_points.push_back(RRT::Intersection(t2, sphere));
			}
			else
			{
				xs_points.push_back(RRT::Intersection(t2, sphere));
				xs_points.push_back(RRT::Intersection(t1, sphere));
			}
		}

		return xs_points;
	}

	std::tuple<bool, RRT::Intersection> Hit(const std::vector<RRT::Intersection>& xs_vec)
	{
		bool hit_flag = false;
		RRT::Sphere s = RRT::Sphere(0);
		RRT::Intersection final_xs = RRT::Intersection(1e10f, s);

		for (const auto& xs : xs_vec)
		{
			if (xs.Time() > 0.0f && xs.Time() < final_xs.Time())
			{
				final_xs = xs;
				hit_flag = true;
			}
		}

		return std::make_tuple(hit_flag, final_xs);
	}

	RRT::Ray Transform(const RRT::Ray& ray, const RRT::Matrix& matrix)
	{	
		RRT::Tuple new_origin = matrix * ray.Origin();		
		RRT::Tuple new_direction = matrix * ray.Direction();
		RRT::Ray new_ray(new_origin, new_direction);

		return new_ray;
	}

	RRT::Tuple Normal_At(const RRT::Sphere& sphere, const RRT::Tuple& point)
	{
		float x{ 0.0f };
		float y{ 0.0f };
		float z{ 0.0f };

		return RRT::TupleFactory().Vector(x, y, z);
	}
}