#ifndef CANVAS
#define CANVAS

#include "Color.hpp"

#include <vector>

namespace RRT
{
	class Canvas
	{
	public:
		Canvas() = delete;
		Canvas(size_t width, size_t height);

		size_t Width() const noexcept { return width; }
		size_t Height() const noexcept { return height; }

		std::vector<std::vector<Color>> PixelMap() const noexcept { return pixel_map; }

	private:

		std::vector<std::vector<Color>> pixel_map;
		
		size_t width = 0;
		size_t height = 0;
	};

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


#endif // !CANVAS