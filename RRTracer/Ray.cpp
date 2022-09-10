#include "Ray.h"

namespace RRT
{
	Tuple Ray::Position(const float& t) const
	{
		return (origin + direction * t);
	}
}