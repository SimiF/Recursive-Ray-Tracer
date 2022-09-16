#include "Intersection.h"

namespace RRT
{
	Intersection::Intersection(const Intersection& copy) noexcept(false)
	{
		*this = copy;
	}

	Intersection& Intersection::operator=(const Intersection& rhs) noexcept(false)
	{
		if (this != &rhs)
		{
			time = rhs.time;
			sphere = rhs.sphere;
		}

		return *this;
	}

	Intersection::Intersection(Intersection&& copy) noexcept
	{
		*this = std::move(copy);
	}

	Intersection& Intersection::operator=(Intersection&& rhs) noexcept
	{
		if (this != &rhs)
		{
			time = rhs.time;
			sphere = rhs.sphere;
		}

		return *this;
	}
}