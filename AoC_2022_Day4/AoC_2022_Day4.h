#pragma once

#include <vector>
#include <unordered_map>
#include <range/v3/all.hpp>
#include "delimitered.h"

namespace aoc2022::day4
{
	struct puzzle_input
	{
		std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> assignments;
	};

	std::istream& operator>>(std::istream& is, puzzle_input& input)
	{
		input.assignments = ranges::istream_view<delimitered_pair<delimitered_pair<int,int,'-'>, delimitered_pair<int, int, '-'>>>(is) | ranges::to<std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>>;

		return is;
	}

	bool pair_contains(std::pair<int, int> first, std::pair<int, int> second)
	{
		return (first.first <= second.first && first.second >= second.second) ||
			(first.first >= second.first && first.second <= second.second);
	}

	bool pair_overlaps(std::pair<int, int> first, std::pair<int, int> second)
	{
		return (first.first >= second.first && first.first <= second.second) ||
			(second.first >= first.first && second.first <= first.second);
	}

	int64_t part1(const puzzle_input& input)
	{
		return ranges::count_if(input.assignments, [](auto&& i)
			{
				return pair_contains(i.first, i.second);
			});
	}

	int64_t part2(const puzzle_input& input)
	{
		return ranges::count_if(input.assignments, [](auto&& i)
			{
				return pair_overlaps(i.first, i.second);
			});
	}
}
