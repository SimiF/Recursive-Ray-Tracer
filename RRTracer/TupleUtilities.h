#ifndef RRTTUPLEUTILS_TUPLEUTILITIES_HPP
#define RRTTUPLEUTILS_TUPLEUTILITIES_HPP

#include "Tuple.h"

namespace RRTTupleUtils
{
	inline RRT::Tuple Normalize(const RRT::Tuple& tuple)
	{
		float magnitude = tuple.magnitude();
		float x_norm = tuple.X() / magnitude;
		float y_norm = tuple.Y() / magnitude;
		float z_norm = tuple.Z() / magnitude;
		return { x_norm, y_norm, z_norm, tuple.W() };
	}

	inline float Dot(const RRT::Tuple& tuple_one, const RRT::Tuple& tuple_two)
	{
		float dot_product = tuple_one.X() * tuple_two.X() + tuple_one.Y() * tuple_two.Y() + tuple_one.Z() * tuple_two.Z() + tuple_one.W() * tuple_two.W();
		return dot_product;
	}

	inline RRT::Tuple Cross(const RRT::Tuple& tuple_one, const RRT::Tuple& tuple_two)
	{
		float y_z = tuple_one.Y() * tuple_two.Z() - tuple_one.Z() * tuple_two.Y();
		float z_x = tuple_one.Z() * tuple_two.X() - tuple_one.X() * tuple_two.Z();
		float x_y = tuple_one.X() * tuple_two.Y() - tuple_one.Y() * tuple_two.X();

		return { y_z, z_x, x_y, 0.0f };
	}
}

#endif // !RRTTUPLEUTILS_TUPLEUTILITIES_HPP