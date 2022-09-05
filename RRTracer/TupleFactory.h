#ifndef RRT_TUPLEFACTORY_HPP
#define RRT_TUPLEFACTORY_HPP

#include "Tuple.h"

namespace RRT
{
	class TupleFactory
	{
	public:
		TupleFactory() {};

		Tuple Point(float x, float y, float z);
		Tuple Vector(float x, float y, float z);
	};

	
}

#endif // !RRT_TUPLEFACTORY_HPP