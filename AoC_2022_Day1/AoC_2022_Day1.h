#pragma once

#include <vector>
#include <range/v3/all.hpp>
#include "../Common/stream_line.h"

namespace aoc2022::day1
{
	struct puzzle_input
	{
		std::vector<std::vector<int>> elf_calories;
	};

	std::istream& operator>>(std::istream& is, puzzle_input& input)
	{
		input.elf_calories =
			ranges::istream_view<line<std::optional<int>>>(is) |
			ranges::views::transform([](auto i) { return i.data.value_or(-1); }) |
			ranges::views::split(-1) |
			ranges::to<std::vector<std::vector<int>>>;

		return is;
	}

	int64_t part1(const puzzle_input& input)
	{
		return ranges::max(input.elf_calories |
			ranges::views::transform([](auto i) { return ranges::accumulate(i, 0); }));
	}

	int64_t part2(const puzzle_input& input)
	{
		auto sorted = input.elf_calories |
			ranges::views::transform([](auto i) { return ranges::accumulate(i, 0); }) |
			ranges::to<std::vector> | ranges::actions::sort(ranges::greater());
		return ranges::accumulate(sorted | ranges::views::take(3), 0);
	}
}
