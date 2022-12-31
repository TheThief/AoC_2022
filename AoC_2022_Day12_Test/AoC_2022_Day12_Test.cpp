#include "CppUnitTest.h"

#include <sstream>
#include <string_view>
#include "../AoC_2022_Day12/AoC_2022_Day12.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace aoc2022::day12::test
{
	const std::string test_input =
R"(Sabqponm
abcryxxl
accszExk
acctuvwj
abdefghi)";

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
			const int expected_test_ouput_1 = 31;
			Assert::AreEqual(expected_test_ouput_1, part1(input));
		}

		TEST_METHOD(Part2)
		{
			const int expected_test_ouput_2 = 29;
			Assert::AreEqual(expected_test_ouput_2, part2(input));
		}
	};
}
