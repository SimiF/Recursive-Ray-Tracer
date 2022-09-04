#ifndef PROJECTILE_TEST
#define PROJECTILE_TEST

#include "Tuple.hpp"
#include "TupleFactory.hpp"

class Projectile
{
public:
	Projectile(const RRT::Tuple& position, const RRT::Tuple& velocity)
		: position(position), velocity(velocity) {}

	inline RRT::Tuple Position() const noexcept { return position;  }
	inline RRT::Tuple Velocity() const noexcept { return velocity; }	

	void UpdateProjectile(const RRT::Tuple& new_velocity);

private:
	RRT::Tuple position;
	RRT::Tuple velocity;
};

void Projectile::UpdateProjectile(const RRT::Tuple& new_velocity)
{
	position = position + new_velocity;
	velocity = new_velocity;
}

class Environment
{
public:
	Environment(const RRT::Tuple& gravity,const RRT::Tuple& wind)
		: gravity(gravity), wind(wind) {}

	inline RRT::Tuple Gravity() const noexcept { return gravity; }
	inline RRT::Tuple Wind() const noexcept { return wind;  }

private:
	RRT::Tuple gravity;
	RRT::Tuple wind;
};

#endif // !PROJECTILE_TEST