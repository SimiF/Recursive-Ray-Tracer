#include "Tuple.h"

namespace RRT
{
	Tuple::Tuple(const std::initializer_list<float>& list)
	{
		if (list.size() == 4)
		{
			auto it = list.begin();
			x = it[0];
			y = it[1];
			z = it[2];
			w = it[3];
		}
	}

	Tuple Tuple::operator+(const Tuple& tuple) const
	{
		return { x + tuple.X(), y + tuple.Y(), z + tuple.Z(), w + tuple.W() };
	}

	Tuple Tuple::operator-(const Tuple& tuple) const
	{
		return { x - tuple.X(), y - tuple.Y(), z - tuple.Z(), w - tuple.W() };
	}

	Tuple Tuple::operator-() const
	{
		return { -x, -y, -z, w };
	}

	Tuple Tuple::operator*(const float& f) const
	{
		return { x * f, y * f, z * f, w };
	}

	Tuple Tuple::operator/(const float& f) const
	{
		return { x / f, y / f, z / f, w };
	}

	bool operator==(const Tuple& t1, const Tuple& t2)
	{
		if (RRTUtils::s_floats_equal(t1.X(), t2.X())
			&& RRTUtils::s_floats_equal(t1.Y(), t2.Y())
			&& RRTUtils::s_floats_equal(t1.Z(), t2.Z())
			&& RRTUtils::s_floats_equal(t1.W(), t2.W()))
		{
			return true;
		}

		return false;
	}

	bool operator!=(const Tuple& t1, const Tuple& t2)
	{
		return t1 != t2;
	}

	float Tuple::magnitude() const
	{
		if (IsVector())
		{
			return { sqrtf(x * x + y * y + z * z) };
		}
		else
		{
			return { 0.0 };
		}
	}
}