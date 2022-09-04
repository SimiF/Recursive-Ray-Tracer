#include "pch.h"
#include "CppUnitTest.h"

#include "../RRTracer/Color.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RRT_Color_UnitTests
{
	TEST_CLASS(RRT_Color_Constructor_Tests)
	{
	public:
		TEST_METHOD(Color_Constructor_Test)
		{
			RRT::Color c{ -0.5f, 0.4f, 1.7f };

			Assert::AreEqual(-0.5f, c.Red());
			Assert::AreEqual(0.4f, c.Green());
			Assert::AreEqual(1.7f, c.Blue());
		}
	};
}