#ifndef RAY_UTILITIES_H
#define RAY_UTILITIES_H

#include "Ray.h"
#include "Sphere.h"
#include "Tuple.h"
#include "TupleFactory.h"
#include "TupleUtilities.h"
#include "Intersection.h"
#include "Utilities.h"
#include "Matrix.h"
#include "MatrixUtilities.h"
#include "PointLight.h"

#include <algorithm>
#include <tuple>
#include <vector>
#include <cmath>
#include <optional>

namespace RRTRayUtils
{
	std::vector<RRT::Intersection> Intersects(const RRT::Sphere& sphere, const RRT::Ray& ray);
	std::optional<RRT::Intersection> Hit(const std::vector<RRT::Intersection>& xs_vec);
	RRT::Ray Transform(const RRT::Ray& ray, const RRT::Matrix& matrix);
	RRT::Tuple Normal_At(const RRT::Sphere& sphere, const RRT::Tuple& point);
	RRT::Tuple Reflect(const RRT::Tuple& in_vec, const RRT::Tuple& in_norm);
	RRT::Color Lighting(const RRT::Material& material, const RRT::Tuple& point_at, const RRT::PointLight& light_source, const RRT::Tuple& eye_vec, const RRT::Tuple& norm_vec);
}

#endif // !RAY_UTILITIES_H