#ifndef TUPLE
#define TUPLE

#include <initializer_list>
#include <cmath>

#include "Utilities.hpp"

namespace RRT
{
	class Tuple
	{
	public:
		Tuple() = delete;
		Tuple(float x, float y, float z, float w) : x{ x }, y{ y }, z{ z }, w{ w } {}
		Tuple(const std::initializer_list<float>& list);

		Tuple operator+(const Tuple& tuple) const;
		Tuple operator-(const Tuple& tuple) const;

		Tuple operator-() const;

		Tuple operator*(const float& f) const;
		Tuple operator/(const float& f) const;

		inline float magnitude() const;

		inline bool IsPoint() const noexcept { return RRTUtils::s_floats_equal(w, 1.0f); }
		inline bool IsVector() const noexcept { return !IsPoint(); }

		float X() const noexcept { return x; }
		float Y() const noexcept { return y; }
		float Z() const noexcept { return z; }
		float W() const noexcept { return w; }

	private:
		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;
		float w = -1.0f;
	};

	Tuple::Tuple(const std::initializer_list<float>&list)
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

	inline float Tuple::magnitude() const
	{
		if (IsVector())
		{
			return { sqrtf(x * x + y * y + z * z)};
		}
		else
		{
			return { 0.0 };
		}
	}
}

#endif // !TUPLE