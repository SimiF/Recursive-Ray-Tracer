#include "Canvas.h"

#include <fstream>
#include <cmath>
#include <sstream>

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

	bool Canvas::Write(const std::string& file_name) const
	{
		bool scs_write = false;
		std::ofstream ppm_file(file_name);

		ppm_file << "P3\n";
		ppm_file << width << ' ' << height << '\n';

  		unsigned int current_char_pos = 0;
		unsigned int ppm_row_limit = 70;

		for (const auto& pixel_row : pixel_map)
		{
			for (const auto& pixel : pixel_row)
			{
				if (pixel.Red() == 1.00f)
				{
					int hello = 1;
				}

				unsigned int red_pixel = (unsigned int) fabsf(pixel.Red() * 255.0f);
				unsigned int green_pixel = (unsigned int)fabsf(pixel.Green() * 255.0f);
				unsigned int blue_pixel = (unsigned int)fabsf(pixel.Blue() * 255.0f);

				if (red_pixel > 255) { red_pixel = 255; }
				if (green_pixel > 255) { green_pixel = 255; }
				if (blue_pixel > 255) { blue_pixel = 255; }

				ppm_file << red_pixel << ' ' << green_pixel << ' ' << blue_pixel << ' ';

				current_char_pos += 6;

				if (current_char_pos > ppm_row_limit)
				{
					ppm_file << '\n';
					current_char_pos = 0;
				}
			}
		}

		ppm_file.close();

		return scs_write;
	}


	std::string Canvas::PixelMapPPMFormat() const
	{	
		std::ostringstream ppm_stream;

		ppm_stream << "P3\n";
		ppm_stream << width << ' ' << height << '\n';
		ppm_stream << "255\n";

		unsigned int current_char_pos = 0;
		unsigned int ppm_row_limit = 70;

		for (const auto& pixel_row : pixel_map)
		{
			for (const auto& pixel : pixel_row)
			{
				if (pixel.Red() == 1.00f)
				{
					int hello = 1;
				}

				unsigned int red_pixel = (unsigned int)fabsf(pixel.Red() * 255.0f);
				unsigned int green_pixel = (unsigned int)fabsf(pixel.Green() * 255.0f);
				unsigned int blue_pixel = (unsigned int)fabsf(pixel.Blue() * 255.0f);

				if (red_pixel > 255) { red_pixel = 255; }
				if (green_pixel > 255) { green_pixel = 255; }
				if (blue_pixel > 255) { blue_pixel = 255; }

				ppm_stream << red_pixel << ' ' << green_pixel << ' ' << blue_pixel << ' ';

				current_char_pos += 6;

				if (current_char_pos > ppm_row_limit)
				{
					ppm_stream << '\n';
					current_char_pos = 0;
				}
			}
		}

		return ppm_stream.str();
	}
}