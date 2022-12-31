#pragma once

#include <vector>
#include <queue>
#include <set>

#include <range/v3/all.hpp>
#include "ranges_utils.h"

namespace aoc2022::day12
{
	struct puzzle_input
	{
		std::vector<std::string> grid;

		friend std::istream& operator>>(std::istream& is, puzzle_input& input)
		{
			input.grid = ranges::getlines(is) | ranges::to<std::vector>;

			return is;
		}
	};

	bool can_step(char from, char to)
	{
		if (from == 'S')
			return (to <= 'b');
		if (to == 'E')
			return (from >= 'y');
		return (to <= from + 1);
	}

	using coordinate = std::pair<int, int>;

	int part1(const puzzle_input& input)
	{
		coordinate grid_size = { (int)ranges::size(input.grid[0]), (int)ranges::size(input.grid) };
		coordinate start = find_val_if(
			input.grid |
			ranges::views::enumerate |
			ranges::views::transform(
				[](auto&& i) { return std::pair((int)index_of(i.second, 'S'), (int)i.first); }),
			[&](auto&& i) { return i.first != grid_size.first; });
		std::queue<std::pair<coordinate, int>> heads; heads.push({start, 0});
		std::set<coordinate> visited; visited.insert(start);

		do
		{
			auto head = heads.front(); heads.pop();
			char from = input.grid[head.first.second][head.first.first];
			if (from == 'E')
				return head.second;
			if (head.first.first > 0 && !visited.contains({ head.first.first - 1, head.first.second }) && can_step(from, input.grid[head.first.second][head.first.first - 1]))
			{
				heads.push({ {head.first.first - 1, head.first.second}, head.second + 1 });
				visited.insert({ head.first.first - 1, head.first.second });
			}
			if (head.first.first < grid_size.first - 1 && !visited.contains({ head.first.first + 1, head.first.second }) && can_step(from, input.grid[head.first.second][head.first.first + 1]))
			{
				heads.push({ {head.first.first + 1, head.first.second}, head.second + 1 });
				visited.insert({ head.first.first + 1, head.first.second });
			}
			if (head.first.second > 0 && !visited.contains({ head.first.first, head.first.second - 1 }) && can_step(from, input.grid[head.first.second - 1][head.first.first]))
			{
				heads.push({ {head.first.first, head.first.second - 1}, head.second + 1 });
				visited.insert({ head.first.first, head.first.second - 1 });
			}
			if (head.first.second < grid_size.second - 1 && !visited.contains({ head.first.first, head.first.second + 1 }) && can_step(from, input.grid[head.first.second + 1][head.first.first]))
			{
				heads.push({ {head.first.first, head.first.second + 1}, head.second + 1 });
				visited.insert({ head.first.first, head.first.second + 1 });
			}
		} while (heads.size() > 0);

		return 0;
	}

	int part2(const puzzle_input& input)
	{
		coordinate grid_size = { (int)ranges::size(input.grid[0]), (int)ranges::size(input.grid) };
		auto starts = input.grid |
			ranges::views::enumerate |
			ranges::views::transform([](auto&& i)
				{
					return i.second |
						ranges::views::enumerate |
						ranges::views::filter([](auto&& j) { return j.second == 'S' || j.second == 'a'; }) |
						ranges::views::transform(
							[i_f=i.first](auto&& j) { return std::pair((int)j.first, (int)i_f); });
				}) |
			ranges::views::join;

		std::queue<std::pair<coordinate, int>> heads( starts |
			ranges::views::transform([](auto&& i) { return std::pair(i, 0); }) |
			ranges::to<std::deque>);
		std::set<coordinate> visited = starts | ranges::to<std::set>;

		do
		{
			auto head = heads.front(); heads.pop();
			char from = input.grid[head.first.second][head.first.first];
			if (from == 'E')
				return head.second;
			if (head.first.first > 0 && !visited.contains({ head.first.first - 1, head.first.second }) && can_step(from, input.grid[head.first.second][head.first.first - 1]))
			{
				heads.push({ {head.first.first - 1, head.first.second}, head.second + 1 });
				visited.insert({ head.first.first - 1, head.first.second });
			}
			if (head.first.first < grid_size.first - 1 && !visited.contains({ head.first.first + 1, head.first.second }) && can_step(from, input.grid[head.first.second][head.first.first + 1]))
			{
				heads.push({ {head.first.first + 1, head.first.second}, head.second + 1 });
				visited.insert({ head.first.first + 1, head.first.second });
			}
			if (head.first.second > 0 && !visited.contains({ head.first.first, head.first.second - 1 }) && can_step(from, input.grid[head.first.second - 1][head.first.first]))
			{
				heads.push({ {head.first.first, head.first.second - 1}, head.second + 1 });
				visited.insert({ head.first.first, head.first.second - 1 });
			}
			if (head.first.second < grid_size.second - 1 && !visited.contains({ head.first.first, head.first.second + 1 }) && can_step(from, input.grid[head.first.second + 1][head.first.first]))
			{
				heads.push({ {head.first.first, head.first.second + 1}, head.second + 1 });
				visited.insert({ head.first.first, head.first.second + 1 });
			}
		} while (heads.size() > 0);

		return 0;
	}
}
