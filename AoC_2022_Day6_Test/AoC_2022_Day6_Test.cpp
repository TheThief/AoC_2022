#include "CppUnitTest.h"

#include <sstream>
#include <string_view>
#include "../AoC_2022_Day6/AoC_2022_Day6.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace aoc2022::day6::test
{
	const std::string test_input =
R"(mjqjpqmgbljsphdztnvjfqwrcgsmlb)";

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
			const int expected_test_ouput_1 = 7;
			Assert::AreEqual(expected_test_ouput_1, part1(input));
		}

		TEST_METHOD(Part2)
		{
			const int expected_test_ouput_2 = 19;
			Assert::AreEqual(expected_test_ouput_2, part2(input));
		}
	};
}
