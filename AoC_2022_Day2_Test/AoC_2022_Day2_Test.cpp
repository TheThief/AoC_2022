#include "CppUnitTest.h"

#include <sstream>
#include <string_view>
#include "../AoC_2022_Day2/AoC_2022_Day2.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace aoc2022::day2::test
{
	const std::string test_input =
R"(A Y
B X
C Z)";

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
			const int64_t expected_test_ouput_1 = 15;
			Assert::AreEqual(expected_test_ouput_1, part1(input));
		}

		TEST_METHOD(Part2)
		{
			const int64_t expected_test_ouput_2 = 12;
			Assert::AreEqual(expected_test_ouput_2, part2(input));
		}
	};
}
