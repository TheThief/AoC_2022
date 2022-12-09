#pragma once

#include <vector>

#include <range/v3/all.hpp>
#include "digit.h"
#include "stream_line.h"

namespace aoc2022::day8
{
	struct puzzle_input
	{
		std::vector<std::vector<int>> tree_grid;
	};

	std::istream& operator>>(std::istream& is, puzzle_input& input)
	{
		input.tree_grid = ranges::istream_view<line<std::vector<digit>>>(is) | ranges::to<std::vector<std::vector<int>>>;

		return is;
	}

	auto indices_2d(ranges::forward_range auto& input)
	{
		return ranges::views::cartesian_product(ranges::views::indices(ranges::size(input)), ranges::views::indices(ranges::size(input[0])));
	}

	bool is_visible(const puzzle_input& input, std::tuple<size_t,size_t> yx)
	{
		auto& [y, x] = yx;
		if (y == 0 || x == 0 || y == (input.tree_grid.size() - 1) || x == (input.tree_grid[y].size() - 1))
			return true;

		int height = input.tree_grid[y][x];

		auto&& row = input.tree_grid[y];
		auto&& column = input.tree_grid | ranges::views::transform([x](auto&& i) { return i[x]; });

		auto shorter = [height](auto&& i) { return i < height; };
		return
			ranges::all_of(row    | ranges::views::take(x),     shorter) ||
			ranges::all_of(row    | ranges::views::drop(x + 1), shorter) ||
			ranges::all_of(column | ranges::views::take(y),     shorter) ||
			ranges::all_of(column | ranges::views::drop(y + 1), shorter);
	}

	int scenic_score(const puzzle_input& input, std::tuple<size_t, size_t> yx)
	{
		auto& [y, x] = yx;
		if (y == 0 || x == 0 || y == (input.tree_grid.size() - 1) || x == (input.tree_grid[y].size() - 1))
			return 0;

		int height = input.tree_grid[y][x];

		auto&& row = input.tree_grid[y];
		auto&& column = input.tree_grid | ranges::views::transform([x](auto&& i) { return i[x]; });

		auto shorter = [height](auto&& i) { return i < height; };
		return
			(1+ranges::distance(row    | ranges::views::take(x)     | ranges::views::drop(1)      | ranges::views::reverse | ranges::views::take_while(shorter))) *
			(1+ranges::distance(row    | ranges::views::drop(x + 1) | ranges::views::drop_last(1)                          | ranges::views::take_while(shorter))) *
			(1+ranges::distance(column | ranges::views::take(y)     | ranges::views::drop(1)      | ranges::views::reverse | ranges::views::take_while(shorter))) *
			(1+ranges::distance(column | ranges::views::drop(y + 1) | ranges::views::drop_last(1)                          | ranges::views::take_while(shorter)));
	}

	int part1(const puzzle_input& input)
	{
		return (int)ranges::count_if(indices_2d(input.tree_grid), [&input](auto&& i) { return is_visible(input, i); });
	}

	int part2(const puzzle_input& input)
	{
		return ranges::max(indices_2d(input.tree_grid) |
			ranges::views::transform([&input](auto&& i) { return scenic_score(input, i); }));
	}
}
