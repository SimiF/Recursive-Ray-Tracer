#include "Color.h"

namespace RRT
{
	Color::Color(const std::initializer_list<float>& list)
	{
		if (list.size() == 3)
		{
			auto it = list.begin();
			red = it[0];
			green = it[1];
			blue = it[2];
		}
	}

	Color Color::operator+(const Color& color) const
	{
		return { red + color.Red(), green + color.Green(), blue + color.Blue() };
	}

	Color Color::operator-(const Color& color) const
	{
		return { red - color.Red(), green - color.Green(), blue - color.Blue() };
	}

	Color Color::operator*(const Color& color) const
	{
		return { red * color.Red(), green * color.Green(), blue * color.Blue() };
	}

	Color Color::operator*(const float& f) const
	{
		return { red * f, green * f, blue * f };
	}

	Color Color::operator/(const float& f) const
	{
		return { red / f, green / f, blue / f };
	}

	bool operator==(const Color& t1, const Color& t2)
	{
		return RRTUtils::s_floats_equal(t1.Red(), t2.Red())
			&& RRTUtils::s_floats_equal(t1.Green(), t2.Green())
			&& RRTUtils::s_floats_equal(t1.Blue(), t2.Blue());
	}

	bool operator!=(const Color& t1, const Color& t2)
	{
		return !(t1 == t2);
	}
}