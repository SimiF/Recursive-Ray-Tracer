#ifndef RAY_UTILITIES_H
#define RAY_UTILITIES_H

#include "Ray.h"
#include "Sphere.h"
#include "Tuple.h"
#include "TupleFactory.h"
#include "TupleUtilities.h"

#include <tuple>
#include <vector>]
#include <cmath>

namespace RRTRayUtils
{
	std::tuple<bool, std::vector<float>> Intersects(const RRT::Sphere& sphere, const RRT::Ray& ray);
}

#endif // !RAY_UTILITIES_H