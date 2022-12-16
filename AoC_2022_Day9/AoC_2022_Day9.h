#pragma once

#include <vector>
#include <set>

#include <range/v3/all.hpp>
#include "digit.h"
#include "stream_line.h"

namespace aoc2022::day9
{
	struct step
	{
		char direction;
		int distance;

		friend std::istream& operator>>(std::istream& is, step& s)
		{
			is >> s.direction >> s.distance;
			return is;
		}
	};

	struct puzzle_input
	{
		std::vector<step> steps;

		friend std::istream& operator>>(std::istream& is, puzzle_input& input)
		{
			input.steps = ranges::istream_view<step>(is) | ranges::to<std::vector<step>>;

			return is;
		}
	};

	using coordinate = std::pair<int, int>;

	void step_head(coordinate& head, char dir)
	{
		switch (dir)
		{
		case 'U':
			head.second -= 1;
			break;
		case 'D':
			head.second += 1;
			break;
		case 'L':
			head.first -= 1;
			break;
		case 'R':
			head.first += 1;
			break;
		}
	}

	template <typename T> int sgn(T val) {
		return (T(0) < val) - (val < T(0));
	}

	int distance(coordinate& head, coordinate& tail)
	{
		return std::max(std::abs(head.first - tail.first), std::abs(head.second - tail.second));
	}

	void step_tail(const coordinate& head, coordinate& tail)
	{
		tail.first += sgn(head.first - tail.first);
		tail.second += sgn(head.second - tail.second);
	}

	int part1(const puzzle_input& input)
	{
		coordinate head = { 0, 0 };
		coordinate tail = { 0, 0 };
		std::set<coordinate> tail_visited = { tail };

		for (auto&& s : input.steps)
		{
			for (int d = 0; d < s.distance; ++d)
			{
				step_head(head, s.direction);
				if (distance(head, tail) > 1)
				{
					step_tail(head, tail);
					tail_visited.insert(tail);
				}
			}
		}

		return tail_visited.size();
	}

	int part2(const puzzle_input& input)
	{
		std::array<coordinate, 10> rope = {{ { 0, 0 } }};
		std::set<coordinate> tail_visited = { rope[9] };

		for (auto&& s : input.steps)
		{
			for (int d = 0; d < s.distance; ++d)
			{
				step_head(rope[0], s.direction);
				for (int i = 1; i < 9; ++i)
				{
					if (distance(rope[i - 1], rope[i]) > 1)
					{
						step_tail(rope[i - 1], rope[i]);
					}
				}

				if (distance(rope[8], rope[9]) > 1)
				{
					step_tail(rope[8], rope[9]);
					tail_visited.insert(rope[9]);
				}
			}
		}

		return tail_visited.size();
	}
}
