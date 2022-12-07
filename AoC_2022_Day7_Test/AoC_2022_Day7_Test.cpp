#include "CppUnitTest.h"

#include <sstream>
#include <string_view>
#include "../AoC_2022_Day7/AoC_2022_Day7.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace aoc2022::day7::test
{
	const std::string test_input =
R"($ cd /
$ ls
dir a
14848514 b.txt
8504156 c.dat
dir d
$ cd a
$ ls
dir e
29116 f
2557 g
62596 h.lst
$ cd e
$ ls
584 i
$ cd ..
$ cd ..
$ cd d
$ ls
4060174 j
8033020 d.log
5626152 d.ext
7214296 k)";

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
			const int expected_test_ouput_1 = 95437;
			Assert::AreEqual(expected_test_ouput_1, part1(input));
		}

		TEST_METHOD(Part2)
		{
			const int expected_test_ouput_2 = 24933642;
			Assert::AreEqual(expected_test_ouput_2, part2(input));
		}
	};
}
