#include "pch.h"
#include "CppUnitTest.h"

#include "../RRTracer/Tuple.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RRTTupleUnitTests
{
	TEST_CLASS(RRTTupleUnitTests)
	{
	public:

		TEST_METHOD(TupleWithWeight1IsAPoint)
		{
			float x{ 4.3 };
			float y{ -4.2 };
			float z{ 3.1 };
			float w{ 1.0 };
			RRT::Tuple tuple = RRT::Tuple(4.3, -4.2, 3.1, 1.0);

			Assert::AreEqual(x, tuple.X());
			Assert::AreEqual(y, tuple.Y());
			Assert::AreEqual(z, tuple.Z());
			Assert::AreEqual(w, tuple.W());			
		}		
	};
}
