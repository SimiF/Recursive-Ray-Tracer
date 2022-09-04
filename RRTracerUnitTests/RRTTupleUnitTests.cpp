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
			float x{ 4.3f };
			float y{ -4.2f };
			float z{ 3.1f };
			float w{ 1.0f };
			RRT::Tuple tuple = RRT::Tuple(4.3f, -4.2f, 3.1f, 1.0f);

			Assert::AreEqual(x, tuple.X());
			Assert::AreEqual(y, tuple.Y());
			Assert::AreEqual(z, tuple.Z());
			Assert::AreEqual(w, tuple.W());		
		}		

		TEST_METHOD(TupleWithWeight0IsAVector)
		{
			float x{ 4.3f };
			float y{ -4.2f };
			float z{ 3.1f };
			float w{ 0.0f };
			RRT::Tuple tuple = RRT::Tuple(4.3f, -4.2f, 3.1f, 0.0f);

			Assert::AreEqual(x, tuple.X());
			Assert::AreEqual(y, tuple.Y());
			Assert::AreEqual(z, tuple.Z());
			Assert::AreEqual(w, tuple.W());
		}
	};
}
