#ifndef POINT
#define POINT

namespace RRT
{
	class Point
	{
	public:
		Point() = delete;
		Point(float x, float y, float z) : x{ x }, y{ y }, z{ z } {}

		float X() const noexcept { return x; }
		float Y() const noexcept { return y; }
		float Z() const noexcept { return z; }
		float W() const noexcept { return w; }

	private:
		float x;
		float y;
		float z;
		float w = 1.0;
	};	
}

#endif // !POINT