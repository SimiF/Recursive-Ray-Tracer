#include "Projectile.h"

void Projectile::UpdateProjectile(const RRT::Tuple& new_velocity)
{
	position = position + new_velocity;
	velocity = new_velocity;
}