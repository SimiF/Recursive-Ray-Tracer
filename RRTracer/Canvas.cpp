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
}