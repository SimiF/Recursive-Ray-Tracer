#ifndef RAY_H
#define RAY_H

#include "Tuple.h"
#include "TupleFactory.h"

namespace RRT
{
	class Ray
	{
	public:
		Ray() = default;
		Ray(const Tuple& ray_origin, const Tuple& ray_direction) : origin(ray_origin), direction(ray_direction) {}

		Tuple Position(const float& t) const;

		inline Tuple Origin() const { return origin; }
		inline Tuple Direction() const { return direction; }
	private:
		Tuple origin = { 0.0f, 0.0f, 0.0f, 1.0f };
		Tuple direction = { 0.0f, 0.0f, 0.0f, 0.0f };
	};
}

#endif // !RAY_H