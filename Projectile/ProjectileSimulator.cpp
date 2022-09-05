#include "ProjectileSimulator.h"

RRT::Canvas ProjectileSimulator::Run()
{
	RRT::Canvas canvas = RRT::Canvas(900, 550);

	while (proj.Position().Y() >= 0.0f)
	{
		size_t x = (unsigned int)proj.Position().X();
		size_t y = canvas.Height() - (unsigned int)proj.Position().Y();

		if (x < canvas.Width() && x >= 0 && y < canvas.Height() && y >= 0)
		{
			canvas.Pixel(x, y) = RRT::Color(1.0f, 1.0f, 1.0f);
		}

		RRT::Tuple new_velocity = proj.Velocity() + proj_env.Gravity() + proj_env.Wind();
		proj.UpdateProjectile(new_velocity);
	}

	return canvas;
}