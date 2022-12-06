#pragma once

#include <vector>
#include <unordered_map>
#include <range/v3/all.hpp>
#include "delimitered.h"
#include "stream_line.h"

namespace aoc2022::day5
{
	struct move
	{
		int count;
		int from;
		int to;

		friend std::istream& operator>>(std::istream& is, move& m)
		{
			is >> required{ "move" } >> m.count >> required{ "from" } >> m.from >> required{ "to" } >> m.to;
			return is;
		}
	};

	struct puzzle_input
	{
		std::vector<std::vector<char>> stacks;
		std::vector<move> moves;
	};

	std::istream& operator>>(std::istream& is, puzzle_input& input)
	{
		std::vector<std::string> stack_lines = ranges::istream_view<line<std::string>>(is) | ranges::views::take_while([](auto&& i) { return i.data != ""; }) | ranges::to<std::vector<std::string>>;

		for (auto&& line : stack_lines | ranges::views::reverse | ranges::views::drop(1))
		{
			int count = (line.length() + 1) / 4;
			if (input.stacks.size() < count)
				input.stacks.resize(count);
			for (auto [index, crate] : line | ranges::views::drop(1) | ranges::views::stride(4) | ranges::views::enumerate | ranges::views::filter([](auto&& i) { return i.second != ' '; }))
			{
				input.stacks[index].push_back(crate);
			}
		}

		input.moves =
			ranges::istream_view<move>(is) | ranges::to<std::vector>;

		return is;
	}

	std::string part1(const puzzle_input& input)
	{
		auto stacks = input.stacks;
		for (auto&& move : input.moves)
		{
			stacks[move.to - 1].append_range(stacks[move.from - 1] | ranges::views::reverse | ranges::views::take(move.count));
			stacks[move.from - 1].resize(stacks[move.from - 1].size() - move.count);
		}
		return stacks | ranges::views::transform([](auto&& i) { return i.back(); }) | ranges::to<std::string>;
	}

	std::string part2(const puzzle_input& input)
	{
		auto stacks = input.stacks;
		for (auto&& move : input.moves)
		{
			stacks[move.to - 1].append_range(stacks[move.from - 1] | ranges::views::take_last(move.count));
			stacks[move.from - 1].resize(stacks[move.from - 1].size() - move.count);
		}
		return stacks | ranges::views::transform([](auto&& i) { return i.back(); }) | ranges::to<std::string>;
	}
}
