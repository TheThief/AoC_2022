#include "CppUnitTest.h"

#include <sstream>
#include <string_view>
#include "../AoC_2022_Day1/AoC_2022_Day1.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace aoc2022::day1::test
{
	const std::string test_input =
		R"(1000
		2000
		3000

		4000

		5000
		6000

		7000
		8000
		9000

		10000)";

	TEST_CLASS(Test)
	{
	public:
		puzzle_input input;

		Test()
		{
			std::istringstream(test_input) >> input;
		}

		TEST_METHOD(Part1)
		{
			const int64_t expected_test_ouput_1 = 24000;
			Assert::AreEqual(expected_test_ouput_1, part1(input));
		}

		TEST_METHOD(Part2)
		{
			const int64_t expected_test_ouput_2 = 45000;
			Assert::AreEqual(expected_test_ouput_2, part2(input));
		}
	};
}
