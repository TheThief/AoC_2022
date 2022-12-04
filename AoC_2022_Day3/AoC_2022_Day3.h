#pragma once

#include <vector>
#include <range/v3/all.hpp>
#include "../Common/stream_line.h"

namespace aoc2022::day3
{
	struct puzzle_input
	{
		std::vector<std::string> bags;
	};

	std::istream& operator>>(std::istream& is, puzzle_input& input)
	{
		input.bags =
			ranges::istream_view<line<std::string>>(is) | ranges::to<std::vector<std::string>>;

		return is;
	}

	int item_to_priority(char item)
	{
		if (item >= 'a' && item <= 'z') return item - 'a' + 1;
		if (item >= 'A' && item <= 'Z') return item - 'A' + 27;
	}

	int64_t part1(const puzzle_input& input)
	{
		return ranges::accumulate(input.bags |
			ranges::views::transform([](auto i) { return std::pair(i.substr(0, i.length() / 2), i.substr(i.length() / 2)); }) |
			ranges::views::transform([](auto i) { return *ranges::find_first_of(i.first, i.second); }) |
			ranges::views::transform(item_to_priority), 0
		);
	}

	int64_t part2(const puzzle_input& input)
	{
		auto sorted = input.bags |
			ranges::views::transform([](std::string i) { ranges::sort(i); return i; }) |
			ranges::to<std::vector>;
		return ranges::accumulate(sorted |
			ranges::views::chunk(3) |
			ranges::views::transform([](auto i)
				{
					return (i[0] |
						ranges::views::set_intersection(i[1]) |
						ranges::views::set_intersection(i[2])
						).front();
				}) |
			ranges::views::transform(item_to_priority), 0
		);
	}
}
