 #ifndef RRT_TUPLE_HPP
#define RRT_TUPLE_HPP

#include <initializer_list>
#include <cmath>

#include "Utilities.h"

namespace RRT
{
	class Tuple
	{
	public:
		Tuple() = default;
		Tuple(float x, float y, float z, float w) : x{ x }, y{ y }, z{ z }, w{ w } {}
		Tuple(const std::initializer_list<float>& list);

		friend bool operator==(const Tuple& t1, const Tuple& t2);
		friend bool operator!=(const Tuple& t1, const Tuple& t2);

		Tuple operator+(const Tuple& tuple) const;
		Tuple operator-(const Tuple& tuple) const;

		Tuple operator-() const;

		Tuple operator*(const float& f) const;
		Tuple operator/(const float& f) const;

		float magnitude() const;

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
}

#endif // !RRT_TUPLE_HPP