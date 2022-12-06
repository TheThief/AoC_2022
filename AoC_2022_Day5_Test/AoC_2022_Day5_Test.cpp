#include "CppUnitTest.h"

#include <sstream>
#include <string_view>
#include "../AoC_2022_Day5/AoC_2022_Day5.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace aoc2022::day5::test
{
	const std::string test_input =
R"(    [D]    
[N] [C]    
[Z] [M] [P]
 1   2   3 

move 1 from 2 to 1
move 3 from 1 to 3
move 2 from 2 to 1
move 1 from 1 to 2)";

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
			const std::string expected_test_ouput_1 = "CMZ";
			Assert::AreEqual(expected_test_ouput_1, part1(input));
		}

		TEST_METHOD(Part2)
		{
			const std::string expected_test_ouput_2 = "MCD";
			Assert::AreEqual(expected_test_ouput_2, part2(input));
		}
	};
}
