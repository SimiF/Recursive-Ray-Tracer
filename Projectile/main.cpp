#include <iostream>
#include <iomanip>

#include "ProjectileSimulator.h"

int main()
{
	auto position_point = RRT::TupleFactory().Point(0.0f, 1.0f, 0.0f);
	auto velocity_vector = RRTTupleUtils::Normalize(RRT::TupleFactory().Vector(1.0f, 1.8f, 0.0f)) * 11.25;
	auto gravity_vector = RRT::TupleFactory().Vector(0.0f, -0.1f, 0.0f);
	auto wind_vector = RRT::TupleFactory().Vector(-0.01f, 0.0f, 0.0f);

	ProjectileSimulator proj_sim(position_point, velocity_vector, gravity_vector, wind_vector);

	RRT::Canvas canvas = RRT::Canvas(900, 550);
	RRT::FileWriter ppm_file_writer("projectile_from_file.ppm");

	canvas = proj_sim.Run();
	ppm_file_writer.Write(canvas.PixelMapPPMFormat());

	return 0;
}