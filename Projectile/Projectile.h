#ifndef PROJECTILE_TEST
#define PROJECTILE_TEST

#include "../RRTracer/Tuple.h"
#include "../RRTracer/TupleFactory.h"

class Projectile
{
public:
	Projectile() = default;
	Projectile(const RRT::Tuple& position, const RRT::Tuple& velocity)
		: position(position), velocity(velocity) {}

	inline RRT::Tuple Position() const noexcept { return position; }
	inline RRT::Tuple Velocity() const noexcept { return velocity; }

	void UpdateProjectile(const RRT::Tuple& new_velocity);

private:
	RRT::Tuple position { 0.0f, 0.0f, 0.0f };
	RRT::Tuple velocity { 0.0f, 0.0f, 0.0f };
};

class Environment
{
public:
	Environment() = default;
	Environment(const RRT::Tuple& gravity, const RRT::Tuple& wind)
		: gravity(gravity), wind(wind) {}

	inline RRT::Tuple Gravity() const noexcept { return gravity; }
	inline RRT::Tuple Wind() const noexcept { return wind; }

private:
	RRT::Tuple gravity{ 0.0f, 0.0f, 0.0f };
	RRT::Tuple wind{ 0.0f, 0.0f, 0.0f };
};

#endif // !PROJECTILE_TEST