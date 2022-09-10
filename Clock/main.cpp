#include <iostream>
#include <vector>

#include "../RRTracer/Tuple.h"
#include "../RRTracer/TupleFactory.h"

#include "../RRTracer/Canvas.h"
#include "../RRTracer/FileWriter.h"

#include "../RRTracer/Transforms.h"

int main()
{
	constexpr float PI{ 3.14159265359f };

	RRT::Canvas canvas = RRT::Canvas(500, 500);
	RRT::FileWriter fw("clock.ppm");

	std::vector<RRT::Tuple> p_vec(12);
	RRT::Matrix rot_m = RRTMatrixTransforms::Rotation_Z((2 * PI) / 12);
	RRT::Matrix scal_m = RRTMatrixTransforms::Scaling(10.0f, 10.0f, 1.0f);
		
	for (auto& p : p_vec)
	{
		p = RRT::TupleFactory().Point(0.0f, 150.0f, 0.0f);
	}	

	for (auto it = p_vec.begin() + 1; it != p_vec.end(); it++)
	{
		*it = rot_m * *std::prev(it);		
	}

	for (const auto& p : p_vec)
	{
		size_t x = (unsigned int)(250.0f - p.X());
		size_t y = (unsigned int)(250.0f - p.Y());

		canvas.Pixel(x, y) = RRT::Color(0.5f, 0.8f, 1.0f);
	}

	fw.Write(canvas.PixelMapPPMFormat());

	return 0;
}