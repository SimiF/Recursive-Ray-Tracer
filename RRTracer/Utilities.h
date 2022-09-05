#ifndef RRTUTILS_UTILITIES_HPP
#define RRTUTILS_UTILITIES_HPP

namespace RRTUtils
{
	inline float s_abs(float a, float b)
	{
		return (a - b) > 0 ? a - b : b - a;
	}

	inline bool s_floats_equal(float a, float b)
	{
		constexpr float EPSILON = 0.00001f;
		bool ret = false;

		if (s_abs(a, b) < EPSILON)
		{
			ret = true;
		}

		return ret;
	}
}

#endif // !RRTUTILS_UTILITIES_HPP