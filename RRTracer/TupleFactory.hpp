#ifndef TUPLE_FACTORY
#define TUPLE_FACTORY

#include "Tuple.hpp"

namespace RRT
{
	class TupleFactory
	{
	public:
		TupleFactory() {};

		static Tuple Point(float x, float y, float z);
		static Tuple Vector(float x, float y, float z);
	};

	Tuple TupleFactory::Point(float x, float y, float z)
	{
		return { x, y, z, 1.0f };
	}

	Tuple TupleFactory::Vector(float x, float y, float z)
	{
		return { x, y, z, 0.0f };
	}
}

#endif // !TUPLE_FACTORY