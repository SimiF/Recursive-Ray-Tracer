#ifndef POINT
#define POINT

#include <initializer_list>

namespace RRT
{
	class Tuple
	{
	public:
		Tuple() = delete;
		Tuple(float x, float y, float z, float w) : x{ x }, y{ y }, z{ z }, w{ w } {}
		Tuple(const std::initializer_list<float>& list);

		float X() const noexcept { return x; }
		float Y() const noexcept { return y; }
		float Z() const noexcept { return z; }
		float W() const noexcept { return w; }

	private:
		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;
		float w = -1.0f;
	};

	Tuple::Tuple(const std::initializer_list<float>&list)
	{
		if (list.size() == 4)
		{
			auto it = list.begin();
			x = it[0];
			y = it[1];
			z = it[2];
			w = it[3];
		}
	}
}

#endif // !POINT