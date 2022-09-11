#ifndef RAY_UTILITIES_H
#define RAY_UTILITIES_H

#include "Ray.h"
#include "Sphere.h"

#include <tuple>
#include <vector>

namespace RRTRayUtils
{
	std::tuple<bool, std::vector<float>> Intersects(const RRT::Sphere& sphere, const RRT::Ray& ray);
}

#endif // !RAY_UTILITIES_H