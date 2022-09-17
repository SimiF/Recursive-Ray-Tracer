#include <iostream>
#include <vector>

#include "../RRTracer/Sphere.h"
#include "../RRTracer/Transforms.h"

#include "../RRTracer/TupleFactory.h"
#include "../RRTracer/TupleUtilities.h"

#include "../RRTracer/Canvas.h"
#include "../RRTracer/FileWriter.h"

#include "../RRTracer/Ray.h"
#include "../RRTracer/RayUtilities.h"
#include "../RRTracer/Intersection.h"

int main()
{
	RRT::Canvas canvas = RRT::Canvas(100, 100);
	RRT::Color sphere_color = { 1.0f, 0.0f, 0.0f };
	RRT::Sphere s(0);
	s.Transform(RRTMatrixTransforms::Rotation_Z(3.14159265 / 4) * RRTMatrixTransforms::Scaling(1.0f, 0.5f, 1.0f));
	RRT::FileWriter fw("shere_render_no_shade.ppm");

	RRT::Tuple ray_origin = RRT::TupleFactory().Point(0.0f, 0.0f, -5.0f);
	float wall_z = 10.0f;
	float wall_size = 7.0f;
	float pixel_size = wall_size / canvas.Height();
	float half = wall_size / 2;

	for (size_t y = 0; y < canvas.Height(); ++y)
	{
		float world_y = half - pixel_size * y;

		RRTUtils::s_display_status(y, canvas.Height());

		for (size_t x = 0; x < canvas.Width(); ++x)
		{
			float world_x = -half + pixel_size * x;

			RRT::Tuple pos = RRT::TupleFactory().Point(world_x, world_y, wall_z);
			RRT::Ray ray = RRT::Ray(ray_origin, RRTTupleUtils::Normalize(pos - ray_origin));
			std::vector<RRT::Intersection> xs = RRTRayUtils::Intersects(s, ray);

			auto [hit, xs_pts] = RRTRayUtils::Hit(xs);
			
			if (hit)
			{				
				canvas.Pixel(x, y) = sphere_color;
			}
		}
	}

	fw.Write(canvas.PixelMapPPMFormat());

	return 0;
}