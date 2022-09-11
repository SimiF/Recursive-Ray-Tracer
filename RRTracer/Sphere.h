#ifndef SPHERE_H
#define SPHERE_H

#include "Tuple.h"

namespace RRT
{
	class Sphere
	{
	public:
		Sphere() = default;

	private:
		Tuple origin = { 0.0f, 0.0f, 0.0f, 1.0f };
		float radius = 0.0f;
	};
}

#endif // !SPHERE_H