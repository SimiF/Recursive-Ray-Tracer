#include "RayUtilities.h"

namespace RRTRayUtils
{
	std::vector<RRT::Intersection> Intersects(const RRT::Sphere& sphere, const RRT::Ray& ray)
	{
		bool hit_flag = false;
		std::vector<RRT::Intersection> xs_points(0);

		RRT::Tuple sphere_to_ray = ray.Origin() - RRT::TupleFactory().Point(0.0f, 0.0f, 0.0f);
		float a = RRTTupleUtils::Dot(ray.Direction(), ray.Direction());
		float b = 2 * RRTTupleUtils::Dot(ray.Direction(), sphere_to_ray);
		float c = RRTTupleUtils::Dot(sphere_to_ray, sphere_to_ray) - 1;
		float discriminant = b * b - (4 * a * c);

		if (discriminant >= 0)
		{
			hit_flag = true;

			float t1 = (-b - sqrtf(discriminant)) / (2 * 1);
			float t2 = (-b + sqrtf(discriminant)) / (2 * 1);

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
		RRT::Intersection xs = RRT::Intersection();

		

		return std::make_tuple(hit_flag, xs);
	}
}