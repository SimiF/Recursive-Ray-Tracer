#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "Color.h"
#include "Tuple.h"
#include "TupleFactory.h"

namespace RRT
{
	class PointLight
	{
	public:
		PointLight() = default;
		PointLight(const RRT::Color& intensity, const RRT::Tuple& position) : intensity(intensity), position(position) {}

		inline RRT::Color Intensity() const { return intensity; }
		inline RRT::Tuple Position() const { return position; }

	private:
		RRT::Color intensity = { 1.0f, 1.0f, 1.0f };
		RRT::Tuple position = RRT::TupleFactory().Point(0.0f, 0.0f, 0.0f);
	};
}

#endif // !POINT_LIGHT_H