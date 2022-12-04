#include "CppUnitTest.h"

#include <sstream>
#include <string_view>
#include "../AoC_2022_Day3/AoC_2022_Day3.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace aoc2022::day3::test
{
	const std::string test_input =
R"(vJrwpWtwJgWrhcsFMMfFFhFp
jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL
PmmdzqPrVvPwwTWBwg
wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn
ttgJtRGJQctTZtZT
CrZsJsPPZsGzwwsLwLmpwMDw)";

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
			const int64_t expected_test_ouput_1 = 157;
			Assert::AreEqual(expected_test_ouput_1, part1(input));
		}

		TEST_METHOD(Part2)
		{
			const int64_t expected_test_ouput_2 = 70;
			Assert::AreEqual(expected_test_ouput_2, part2(input));
		}
	};
}
