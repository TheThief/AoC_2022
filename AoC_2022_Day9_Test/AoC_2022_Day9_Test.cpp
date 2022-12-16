#include "CppUnitTest.h"

#include <sstream>
#include <string_view>
#include "../AoC_2022_Day9/AoC_2022_Day9.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace aoc2022::day9::test
{
	const std::string test_input =
R"(R 4
U 4
L 3
D 1
R 4
D 1
L 5
R 2)";

	const std::string test_input2 =
R"(R 5
U 8
L 8
D 3
R 17
D 10
L 25
U 20)";

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
			const int expected_test_ouput_1 = 13;
			Assert::AreEqual(expected_test_ouput_1, part1(input));
		}

		TEST_METHOD(Part2)
		{
			const int expected_test_ouput_2a = 1;
			Assert::AreEqual(expected_test_ouput_2a, part2(input));

			input = puzzle_input();
			std::istringstream(test_input2) >> input;

			const int expected_test_ouput_2b = 36;
			Assert::AreEqual(expected_test_ouput_2b, part2(input));
		}
	};
}
