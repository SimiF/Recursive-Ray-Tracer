#include "TupleFactory.h"

namespace RRT
{
	Tuple TupleFactory::Point(float x, float y, float z)
	{
		return { x, y, z, 1.0f };
	}

	Tuple TupleFactory::Vector(float x, float y, float z)
	{
		return { x, y, z, 0.0f };
	}
}