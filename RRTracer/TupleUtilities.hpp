#ifndef TUPLE_UTILITIES
#define TUPLE_UTILITIES

#include "Tuple.hpp"

namespace RRTTupleUtils
{
	static RRT::Tuple Normalize(const RRT::Tuple& tuple)
	{
		float magnitude = tuple.magnitude();
		float x_norm = tuple.X() / magnitude;
		float y_norm = tuple.Y() / magnitude;
		float z_norm = tuple.Z() / magnitude;
		return { x_norm, y_norm, z_norm, tuple.W() };
	}
	/*
	static float Dot(const RRT::Tuple& tuple_one, const RRT::Tuple& tuple_two)
	{

	}

	static RRT::Tuple Cross(const RRT::Tuple& tuple_one, const RRT::Tuple& tuple_two)
	{

	}*/
}

#endif // !TUPLE_UTILITIES
