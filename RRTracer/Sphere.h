#ifndef SPHERE_H
#define SPHERE_H

#include "Tuple.h"

namespace RRT
{
	class Sphere
	{
	public:
		Sphere(const int& id) : id(id) {}

		inline int Id() const { return id; }

	private:
		int id = 0;
		Tuple origin = { 0.0f, 0.0f, 0.0f, 1.0f };
		float radius = 0.0f;
	};
}

#endif // !SPHERE_H