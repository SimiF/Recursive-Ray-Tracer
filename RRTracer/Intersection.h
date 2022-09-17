#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "Sphere.h"

#include <utility>

namespace RRT
{
	class Intersection
	{
	public:		
		Intersection() = default;
		Intersection(const float& time, const Sphere& sphere) : time(time), sphere(sphere) {}

		Intersection(const Intersection& copy) noexcept(false);
		Intersection& operator=(const Intersection& rhs) noexcept(false);
		Intersection(Intersection&& copy) noexcept;
		Intersection& operator=(Intersection&& rhs) noexcept;

		inline float Time() const { return time; }
		inline Sphere Object() const { return sphere; }
	private:
		float time = 0.0f;
		Sphere sphere = Sphere(0);
	};
}

#endif // !INTERSECTION_H