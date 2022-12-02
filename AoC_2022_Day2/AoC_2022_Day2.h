#pragma once

#include <vector>
#include <unordered_map>
#include <range/v3/all.hpp>
#include "stream_line.h"

namespace aoc2022::day2
{
	struct puzzle_input
	{
		std::vector<std::string> rounds;
	};

	std::istream& operator>>(std::istream& is, puzzle_input& input)
	{
		input.rounds =
			ranges::istream_view<line<std::string>>(is) |
			ranges::to<std::vector<std::string>>;

		return is;
	}

	// A=Rock B=Paper C=Scissors
	// X=Rock Y=Paper Z=Scissors
	// (Lose=0 Draw=3 Win=6) + (Rock=1 Paper=2 Scissors=3)
	static const std::unordered_map<std::string, int> scores1 =
	{
		{"A X", 3 + 1},
		{"A Y", 6 + 2},
		{"A Z", 0 + 3},
		{"B X", 0 + 1},
		{"B Y", 3 + 2},
		{"B Z", 6 + 3},
		{"C X", 6 + 1},
		{"C Y", 0 + 2},
		{"C Z", 3 + 3},
	};

	int64_t part1(const puzzle_input& input)
	{
		return ranges::accumulate(input.rounds, 0, ranges::plus(), [](auto&& i) { return scores1.at(i); });
	}

	// A=Rock B=Paper C=Scissors
	// X=Lose Y=Draw Z=Win
	// (Lose=0 Draw=3 Win=6) + (Rock=1 Paper=2 Scissors=3)
	static const std::unordered_map<std::string, int> scores2 =
	{
		{"A X", 0 + 3},
		{"A Y", 3 + 1},
		{"A Z", 6 + 2},
		{"B X", 0 + 1},
		{"B Y", 3 + 2},
		{"B Z", 6 + 3},
		{"C X", 0 + 2},
		{"C Y", 3 + 3},
		{"C Z", 6 + 1},
	};

	int64_t part2(const puzzle_input& input)
	{
		return ranges::accumulate(input.rounds, 0, ranges::plus(), [](auto&& i) { return scores2.at(i); });
	}
}
