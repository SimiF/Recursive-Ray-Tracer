#ifndef RAY_UTILITIES_H
#define RAY_UTILITIES_H

#include "Ray.h"
#include "Sphere.h"
#include "Tuple.h"
#include "TupleFactory.h"
#include "TupleUtilities.h"
#include "Intersection.h"
#include "Utilities.h"

#include <algorithm>
#include <tuple>
#include <vector>
#include <cmath>

namespace RRTRayUtils
{
	std::vector<RRT::Intersection> Intersects(const RRT::Sphere& sphere, const RRT::Ray& ray);
	std::tuple<bool, RRT::Intersection> Hit(std::vector<RRT::Intersection>& xs_vec);
}

#endif // !RAY_UTILITIES_H