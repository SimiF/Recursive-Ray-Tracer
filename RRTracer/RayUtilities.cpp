#include "RayUtilities.h"

namespace RRTRayUtils
{
	std::tuple<bool, std::vector<float>> Intersects(const RRT::Sphere& sphere, const RRT::Ray& ray)
	{
		bool hit_flag = false;
		std::vector<float> xs_points(0);

		return std::make_tuple(hit_flag, xs_points);
	}
}