#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "Sphere.h"

namespace RRT
{
	class Intersection
	{
	public:		
		Intersection(const float& time, const Sphere& sphere) : time(time), sphere(sphere) {}

		inline float Time() const { return time; }
	private:
		float time = 0.0f;
		Sphere sphere = Sphere();
	};
}

#endif // !INTERSECTION_H