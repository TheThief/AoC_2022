#pragma once

#include <vector>
#include <unordered_set>
#include <range/v3/all.hpp>
#include "delimitered.h"
#include "stream_line.h"
#include "ranges_utils.h"

namespace aoc2022::day6
{
	struct puzzle_input
	{
		std::string datastream;
	};

	std::istream& operator>>(std::istream& is, puzzle_input& input)
	{
		std::getline(is, input.datastream);

		return is;
	}

	int part1(const puzzle_input& input)
	{
		return index_of_if(input.datastream | ranges::views::sliding(4), [](auto&& i) { return (i | ranges::to<std::unordered_set>).size() == 4; }) + 4;
	}

	int part2(const puzzle_input& input)
	{
		return index_of_if(input.datastream | ranges::views::sliding(14), [](auto&& i) { return (i | ranges::to<std::unordered_set>).size() == 14; }) + 14;
	}
}
