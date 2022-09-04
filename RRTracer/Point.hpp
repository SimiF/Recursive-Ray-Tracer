#ifndef POINT
#define POINT

#include "Tuple.hpp"

namespace RRT
{
	class Point : public Tuple
	{
	public:
		Point() = delete;
		Point(float x, float y, float z) : Tuple(x, y, z, 1.0) {}

	private:
	};
}

#endif // !POINT