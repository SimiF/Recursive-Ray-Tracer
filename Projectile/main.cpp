#include <iostream>
#include <iomanip>

#include "Projectile.h"
#include "../RRTracer/Tuple.h"
#include "../RRTracer/TupleFactory.h"
#include "../RRTracer/TupleUtilities.h"
#include "../RRTracer/Canvas.h"
#include "../RRTracer/Color.h"

void tick(const Environment& e, Projectile& p);

int main()
{
	auto position_point = RRT::TupleFactory().Point(0.0f, 1.0f, 0.0f);
	auto velocity_vector = RRTTupleUtils::Normalize(RRT::TupleFactory().Vector(1.0f, 1.8f, 0.0f)) * 11.25;

	auto gravity_vector = RRT::TupleFactory().Vector(0.0f, -0.1f, 0.0f);
	auto wind_vector = RRT::TupleFactory().Vector(-0.01f, 0.0f, 0.0f);

	Environment e(gravity_vector, wind_vector);
	Projectile p(position_point, velocity_vector);

	tick(e, p);

	return 0;
}

void tick(const Environment& e, Projectile& p)
{
	RRT::Canvas canvas = RRT::Canvas(900, 550);

	int time_in_air = 0;
	while (p.Position().Y() >= 0.0f)
	{
		size_t x = (unsigned int) p.Position().X();
		size_t y = (unsigned int) canvas.Height() - p.Position().Y();

		if (x < canvas.Width() && x >= 0 && y < canvas.Height() && y >= 0)
		{
			canvas.Pixel(x, y) = RRT::Color(1.0f, 1.0f, 1.0f);
		}
		
		std::cout << std::setprecision(2);
		std::cout << std::fixed;
		std::cout << "{ X: " << p.Position().X() << ",\t Y: " << p.Position().Y() << ",\t Z: " << p.Position().Z() << "}\n";
		time_in_air += 1;

		RRT::Tuple new_velocity = p.Velocity() + e.Gravity() + e.Wind();
		p.UpdateProjectile(new_velocity);
	}	

	canvas.Write("projection.ppm");

	std::cout << "Time in air: " << time_in_air << '\n';
}