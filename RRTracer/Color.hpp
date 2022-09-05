#ifndef COLOR
#define COLOR

#include <initializer_list>
#include <cmath>

#include "Utilities.hpp"

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

		float Red() const noexcept { return red; }
		float Green() const noexcept { return green; }
		float Blue() const noexcept { return blue; }

	private:
		float red = 0.0f;
		float green = 0.0f;
		float blue = 0.0f;
	};

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

#endif // !COLOR