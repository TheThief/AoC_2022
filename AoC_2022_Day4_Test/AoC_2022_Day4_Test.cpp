#include "CppUnitTest.h"

#include <sstream>
#include <string_view>
#include "../AoC_2022_Day4/AoC_2022_Day4.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace aoc2022::day4::test
{
	const std::string test_input =
R"(2-4,6-8
2-3,4-5
5-7,7-9
2-8,3-7
6-6,4-6
2-6,4-8)";

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
			const int64_t expected_test_ouput_1 = 2;
			Assert::AreEqual(expected_test_ouput_1, part1(input));
		}

		TEST_METHOD(Part2)
		{
			const int64_t expected_test_ouput_2 = 4;
			Assert::AreEqual(expected_test_ouput_2, part2(input));
		}
	};
}
