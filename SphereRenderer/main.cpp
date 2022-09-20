#include <iostream>
#include <vector>
#include <chrono>
#include <optional>

#include <thread>
#include <mutex>

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

std::mutex canvas_mutex;
std::condition_variable cv;

void cast_ray(int x, int y, RRT::Canvas& canvas)
{
	std::unique_lock lk(canvas_mutex);
	cv.wait(lk);
	const RRT::Tuple ray_origin = RRT::TupleFactory().Point(0.0f, 0.0f, -5.0f);
	const RRT::PointLight light = RRT::PointLight({ 1.0f, 1.0f, 1.0f }, RRT::TupleFactory().Point(0.0f, 0.0f, -10.0f));
	const RRT::Sphere s(0);
	// s.Transform(RRTMatrixTransforms::Rotation_Z(3.14159265359f / 4.0f) * RRTMatrixTransforms::Scaling(1.0f, 0.5f, 1.0f));
	s.Material().Color({ 1.0f, 0.0785f, 0.0f });

	const float wall_z = 10.0f;
	const float wall_size = 7.0f;
	const float pixel_size = wall_size / canvas.Height();
	const float half = wall_size / 2;

	const float world_y = half - pixel_size * y;
	const float world_x = -half + pixel_size * x;

	RRT::Tuple pos = RRT::TupleFactory().Point(world_x, world_y, wall_z);
	RRT::Ray ray = RRT::Ray(ray_origin, RRTTupleUtils::Normalize(pos - ray_origin));

	std::vector<RRT::Intersection> xs1 = RRTRayUtils::Intersects(s, ray);

	std::optional<RRT::Intersection> hit_result = RRTRayUtils::Hit(xs1);

	if (hit_result.has_value())
	{
		RRT::Tuple hit_point = ray.Position(hit_result->Time());
		RRT::Tuple normal_at_hit = RRTRayUtils::Normal_At(hit_result->Object(), hit_point);
		RRT::Tuple eye_vec = -ray.Direction();

		RRT::Color color = RRTRayUtils::Lighting(hit_result->Object().Material(), hit_point, light, eye_vec, normal_at_hit);				
		canvas.Pixel(x, y) = color;
	}

	cv.notify_one();
}

int main()
{	
	std::vector<std::thread> worker_threads(8);
	int i = 0;

	RRT::Canvas canvas = RRT::Canvas(100, 100);		
	RRT::FileWriter fw("shere_render_no_shade.ppm");
		
	auto start_time = std::chrono::high_resolution_clock::now();

	for (size_t y = 0; y < canvas.Height(); ++y)
	{		
		RRTUtils::s_display_status(y, canvas.Height());		

		for (size_t x = 0; x < canvas.Width(); ++x)
		{		
			if (i > 7) { 
				i = 0;			
			}

			worker_threads[i] = std::thread(cast_ray, x, y, std::ref(canvas));

			++i;
		}
	}

	auto finish_time = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = finish_time - start_time;

	std::cout << "Render Time: " << elapsed.count() << '\n';

	fw.Write(canvas.PixelMapPPMFormat());

	return 0;
}