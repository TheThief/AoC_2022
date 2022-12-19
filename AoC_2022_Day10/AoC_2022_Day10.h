#pragma once

#include <unordered_map>
#include <variant>
#include <vector>

#include <range/v3/all.hpp>
#include "stream_required.h"

namespace aoc2022::day10
{
	struct instruction
	{
		std::string command;
		int arg = 0;

		friend std::istream& operator>>(std::istream& is, instruction& input)
		{
			is >> input.command;
			if (input.command == "addx")
			{
				is >> input.arg;
			}
			else
			{
				input.arg = 0;
			}

			return is;
		}
	};


	struct puzzle_input
	{
		std::vector<instruction> program;

		friend std::istream& operator>>(std::istream& is, puzzle_input& input)
		{
			input.program = ranges::istream_view<instruction>(is) | ranges::to<std::vector>;

			return is;
		}
	};

	int part1(const puzzle_input& input)
	{
		auto t = input.program |
			ranges::views::transform([](auto&& i) { return std::pair((i.command == "addx") + 1, i.arg); }) |
			ranges::views::partial_sum(
				[](auto&& a, auto&& b)
				{
					return std::pair(a.first + b.first, a.second + b.second);
				}) |
			// remove all except elements immediately before a boundary - this is the value that register X will contain during the boundary cycle
			ranges::views::adjacent_remove_if([](auto&& a, auto&& b) { return (a.first + 20) / 40 == (b.first + 20) / 40; }) |
			// round up to the boundary and add the initial X value (1)
			ranges::views::transform([](auto&& i) { return std::pair((i.first + 19) / 40 * 40 + 20, i.second + 1); }) |
			ranges::to<std::vector>;
		return ranges::accumulate(t | ranges::views::take(6),
			0, ranges::plus(),
			[](auto&& i) { return (i.first * i.second); });
	}

	std::string part2(const puzzle_input& input)
	{
		auto t = ranges::views::concat(ranges::views::single(std::pair(0, 0)), input.program |
			ranges::views::transform([](auto&& i) { return std::pair((i.command == "addx") + 1, i.arg); }) |
			ranges::views::partial_sum(
				[](auto&& a, auto&& b)
				{
					return std::pair(a.first + b.first, a.second + b.second);
				})) |
			ranges::to<std::vector>;

		std::string result;
		for (int y = 0; y < 6; ++y)
		{
			for (int x = 0; x < 40; ++x)
			{
				int px = y * 40 + x;
				auto dx = --ranges::upper_bound(t, px, ranges::less(), &std::pair<int,int>::first);
				if (x >= dx->second && x <= dx->second + 2)
					result += '#';
				else
					result += '.';

			}
			result += '\n';
		}
		return result;
	}
}
