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
}