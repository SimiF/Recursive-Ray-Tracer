#ifndef RRT_EXCEPTION_H
#define RRT_EXCEPTION_H

#include <exception>
#include <string>

namespace RRT
{
	class RRTException final : public std::exception
	{
	public:
		explicit RRTException(const char* message) : exception(message) {}	
	};
}

#endif // !RRT_EXCEPTION_H