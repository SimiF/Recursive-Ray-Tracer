#ifndef RRT_COLOR_HPP
#define RRT_COLOR_HPP

#include <initializer_list>
#include <cmath>

#include "Utilities.h"

namespace RRT
{
	class Color
	{
	public:
		Color() {}
		Color(float red, float green, float blue) : red{ red }, green{ green }, blue{ blue } {}
		Color(const std::initializer_list<float>& list);

		Color operator+(const Color& color) const;
		Color operator-(const Color& color) const;

		Color operator*(const Color& color) const;

		Color operator*(const float& f) const;
		Color operator/(const float& f) const;

		friend bool operator==(const Color& t1, const Color& t2);
		friend bool operator!=(const Color& t1, const Color& t2);

		float Red() const noexcept { return red; }
		float Green() const noexcept { return green; }
		float Blue() const noexcept { return blue; }

	private:
		float red = 0.0f;
		float green = 0.0f;
		float blue = 0.0f;
	};
}

#endif // !RRT_COLOR_HPP