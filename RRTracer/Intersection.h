#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "Sphere.h"

namespace RRT
{
	class Intersection
	{
	public:		
		Intersection() = default;
		Intersection(const float& time, const Sphere& sphere) : time(time), sphere(sphere) {}

		inline float Time() const { return time; }
		inline Sphere Object() const { return sphere; }
	private:
		float time = 0.0f;
		Sphere sphere = Sphere(0);
	};
}

#endif // !INTERSECTION_H