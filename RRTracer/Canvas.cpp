#include "Canvas.h"

namespace RRT
{
	Canvas::Canvas(size_t w, size_t h)
	{
		width = w;
		height = h;

		pixel_map.resize(height);
		for (auto& pixel_row : pixel_map)
		{
			pixel_row.resize(width);			
		}
	}

	Color& Canvas::Pixel(size_t x, size_t y) noexcept(false)
	{
		return pixel_map[x][y];
	}

	Color Canvas::Pixel(size_t x, size_t y) const noexcept(false)
	{
		return pixel_map[x][y];
	}
}