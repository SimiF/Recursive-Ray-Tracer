#include "Canvas.h"

namespace RRT
{
	Canvas::Canvas(size_t width, size_t height)
	{
		pixel_map.resize(height);
		for (auto& pixel_row : pixel_map)
		{
			pixel_row.resize(width);

			for (auto& pixel : pixel_row)
			{
				pixel = { 0, 0, 0 };
			}
		}
	}
}