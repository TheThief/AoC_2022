#pragma once

#include <vector>
#include <unordered_set>
#include <range/v3/all.hpp>
#include "delimitered.h"
#include "stream_line.h"

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
		// there's no index_of, and find_if returns ranges::dangling when fed a range pipeline (even enumerate), so I need to store a temporary range to be able to subtract begin(). Awful.
		auto temp = input.datastream | ranges::views::sliding(4);
		return ranges::find_if(temp, [](auto&& i) { return (i | ranges::to<std::unordered_set>).size() == 4; }) - temp.begin() + 4;
	}

	int part2(const puzzle_input& input)
	{
		auto temp = input.datastream | ranges::views::sliding(14) | ranges::to<std::vector>;
		return ranges::find_if(temp, [](auto&& i) { return (i | ranges::to<std::unordered_set>).size() == 14; }) - temp.begin() + 14;
	}
}
