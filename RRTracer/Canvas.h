#ifndef RRT_CANVAS_HPP
#define RRT_CANVAS_HPP

#include "Color.h"

#include <vector>
#include <string>

namespace RRT
{
	class Canvas
	{
	public:
		Canvas() = delete;
		Canvas(size_t w, size_t h);

		Color& Pixel(size_t x, size_t y) noexcept(false);
		Color Pixel(size_t x, size_t y) const noexcept(false);

		size_t Width() const noexcept { return width; }
		size_t Height() const noexcept { return height; }
		
		std::string PixelMapPPMFormat() const;

		std::vector<std::vector<Color>> PixelMap() const noexcept { return pixel_map; }

	private:

		std::vector<std::vector<Color>> pixel_map;

		size_t width = 0;
		size_t height = 0;
	};	
}

#endif // !RRT_CANVAS_HPP