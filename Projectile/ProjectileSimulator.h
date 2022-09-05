#ifndef PROJECTILE_SIMULATOR_H
#define PROJECTILE_SIMULATOR_H

#include "Projectile.h"
#include "../RRTracer/Tuple.h"
#include "../RRTracer/TupleFactory.h"
#include "../RRTracer/TupleUtilities.h"
#include "../RRTracer/Canvas.h"
#include "../RRTracer/Color.h"
#include "../RRTracer/FileWriter.h"

class ProjectileSimulator
{
public:	
	ProjectileSimulator(const RRT::Tuple& proj_pos_vec, const RRT::Tuple& proj_vel_vec, const RRT::Tuple& env_grav_vec, const RRT::Tuple& env_wind_vec)
		: proj(proj_pos_vec, proj_vel_vec), proj_env(env_grav_vec, env_wind_vec) {}

	RRT::Canvas Run();

private:
	Projectile proj;
	Environment proj_env;	
};

#endif // !PROJECTILE_SIMULATOR_H