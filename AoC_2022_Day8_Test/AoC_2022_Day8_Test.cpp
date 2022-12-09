#include "CppUnitTest.h"

#include <sstream>
#include <string_view>
#include "../AoC_2022_Day8/AoC_2022_Day8.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace aoc2022::day8::test
{
	const std::string test_input =
R"(30373
25512
65332
33549
35390)";

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
			const int expected_test_ouput_1 = 21;
			Assert::AreEqual(expected_test_ouput_1, part1(input));
		}

		TEST_METHOD(Part2)
		{
			const int expected_test_ouput_2 = 8;
			Assert::AreEqual(expected_test_ouput_2, part2(input));
		}
	};
}
