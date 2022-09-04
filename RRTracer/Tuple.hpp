#ifndef TUPLE
#define TUPLE

namespace RRT
{
	class Tuple
	{
	public:
		Tuple() = delete;
		Tuple(float x, float y, float z, float w)
			: x{ x }, y{ y }, z{ z }, w{ w } {}

		inline float X() const noexcept { return x; }
		inline float Y() const noexcept { return y; }
		inline float Z() const noexcept { return z; }
		inline float W() const noexcept { return w; }

	private:
		float x;
		float y;
		float z;
		float w;
	};
};

#endif // !TUPLE