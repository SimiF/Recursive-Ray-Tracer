#ifndef VECTOR
#define VECTOR

#include "Tuple.hpp"

namespace RRT
{
	class Vector : public Tuple
	{
	public:
		Vector() = delete;
		Vector(float x, float y, float z) : Tuple(x, y, z, 0.0) {}

	private:
	};
}

#endif // !VECTOR