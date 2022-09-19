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

#include "../RRTracer/PointLight.h"

int main()
{
	RRT::PointLight light = RRT::PointLight({ 1.0f, 1.0f, 1.0f }, RRT::TupleFactory().Point(-10.0f, 10.0f, -10.0f));

	RRT::Canvas canvas = RRT::Canvas(200, 200);	
	RRT::Sphere s(0);
	s.Transform(RRTMatrixTransforms::Rotation_Z(3.14159265359f / 4.0f) * RRTMatrixTransforms::Scaling(1.0f, 0.5f, 1.0f));
	s.Material().Color({ 0.274f, 0.705f, 0.705f });
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

			std::vector<RRT::Intersection> xs1 = RRTRayUtils::Intersects(s, ray);			

			auto [hit1, xs_pts1] = RRTRayUtils::Hit(xs1);			
						
			if (hit1)
			{			
				RRT::Tuple hit_point = ray.Position(xs_pts1.Time());
				RRT::Tuple normal_at_hit = RRTRayUtils::Normal_At(xs_pts1.Object(), hit_point);
				RRT::Tuple eye_vec = -ray.Direction();

				RRT::Color color = RRTRayUtils::Lighting(xs_pts1.Object().Material(), hit_point, light, eye_vec, normal_at_hit);

				canvas.Pixel(x, y) = color;
			}			
		}
	}

	fw.Write(canvas.PixelMapPPMFormat());

	return 0;
}