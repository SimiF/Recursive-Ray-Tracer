#include "pch.h"
#include "CppUnitTest.h"

#include <string>

#include "../RRTracer/Canvas.h"
#include "../RRTracer/Color.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RRT_Canvas_UnitTests
{	
	constexpr float EPSILON = 0.0001f;

	TEST_CLASS(RRT_Canvas_UnitTests)
	{
	public:
		TEST_METHOD(Canvas_Constructor_Test)
		{
			size_t width = 10;
			size_t height = 20;

			RRT::Canvas canvas = RRT::Canvas(10, 20);

			Assert::AreEqual(width, canvas.Width());
			Assert::AreEqual(height, canvas.Height());

			auto pixel_map = canvas.PixelMap();
			
			for (const auto& pixel_row : pixel_map)
			{
				for (const auto& pixel : pixel_row)
				{
					Assert::AreEqual(0.0f, pixel.Red(), EPSILON);
					Assert::AreEqual(0.0f, pixel.Green(), EPSILON);
					Assert::AreEqual(0.0f, pixel.Blue(), EPSILON);
				}
			}
		}

		TEST_METHOD(Setting_And_Getting_Pixels)
		{
			size_t width = 10;
			size_t height = 20;

			RRT::Canvas canvas = RRT::Canvas(10, 20);

			Assert::AreEqual(width, canvas.Width());
			Assert::AreEqual(height, canvas.Height());

			canvas.Pixel(1, 1) = RRT::Color(0.2f, 0.1f, 0.9f);

			Assert::AreEqual(0.2f, canvas.Pixel(1, 1).Red());
			Assert::AreEqual(0.1f, canvas.Pixel(1, 1).Green());
			Assert::AreEqual(0.9f, canvas.Pixel(1, 1).Blue());
		}

		TEST_METHOD(Header_file_is_correct_for_PPM3_format)
		{
			std::string expected_header = {"P3\n5 3\n255"};
			RRT::Canvas canvas = RRT::Canvas(5, 3);

			std::string ppm_format = canvas.PixelMapPPMFormat();
			
			bool correct_header = (ppm_format.find(expected_header) != std::string::npos);
			Assert::IsTrue(correct_header);
		}

		TEST_METHOD(Last_character_is_new_line)
		{
			RRT::Canvas canvas = RRT::Canvas(5, 3);

			std::string ppm_format = canvas.PixelMapPPMFormat();

			// never subtract 1 from size_t but this is a controlled scenario where length always > 0
			Assert::AreEqual('\n', ppm_format[ppm_format.length() - 1]);
		}
	};
}