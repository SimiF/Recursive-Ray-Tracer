#ifndef UTILITIES
#define UTILITIES

namespace RRTUtils
{	
	static bool s_floats_equal(float a, float b)
	{
		constexpr float EPSILON = 0.00001;
		bool ret = false;

		if (abs(a, b) < EPSILON)
		{
			ret = true;
		}

		return ret;
	}

	static float abs(float a, float b)
	{
		return (a-b) > 0 ? a-b : b-a ;
	}
}

#endif // !UTILITIES