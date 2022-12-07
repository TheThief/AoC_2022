#pragma once

#include <unordered_map>
#include <variant>
#include <vector>

#include <range/v3/all.hpp>
#include "stream_required.h"

namespace aoc2022::day7
{
	struct line
	{
		struct commandline
		{
			std::string command;
			std::string arg;
		};
		struct file
		{
			std::string name;
			int size;
		};
		struct dir
		{
			std::string name;
		};

		std::variant<commandline, file, dir> value;

		friend std::istream& operator>>(std::istream& is, line& input)
		{
			is >> std::ws;
			if (is.peek() == '$')
			{
				commandline c;
				is >> required{ '$' } >> c.command;
				if (c.command == "cd")
					is >> c.arg;
				input.value = std::move(c);
			}
			else if (is.peek() == 'd')
			{
				dir d;
				is >> required{ "dir" } >> d.name;
				input.value = std::move(d);
			}
			else
			{
				file f;
				is >> f.size >> f.name;
				input.value = std::move(f);
			}

			return is;
		}
	};


	struct puzzle_input
	{
		std::vector<line> terminal_log;
	};

	std::istream& operator>>(std::istream& is, puzzle_input& input)
	{
		input.terminal_log = ranges::istream_view<line>(is) | ranges::to<std::vector>;

		return is;
	}

	std::unordered_map<std::string, int> get_path_to_size(const puzzle_input& input)
	{
		std::vector<std::string> path_stack = {};
		std::unordered_map<std::string, int> path_to_size = { {"/", 0 } };
	
		for (auto&& i : input.terminal_log)
		{
			std::visit([&](auto&& arg)
				{
					using T = std::decay_t<decltype(arg)>;
			if constexpr (std::is_same_v<T, line::commandline>)
			{
				if (arg.command == "cd")
				{
					if (arg.arg == "..")
					{
						path_stack.pop_back();
					}
					else if (arg.arg == "/")
					{
						path_stack = { "/" };
					}
					else
					{
						path_stack.push_back(path_stack.back() + "/" + arg.arg);
					}
				}
			}
			else if constexpr (std::is_same_v<T, line::file>)
			{
				for (auto&& p : path_stack)
				{
					path_to_size[p] += arg.size;
				}
			}
				}, i.value);
		}

		return path_to_size;
	}

	int part1(const puzzle_input& input)
	{
		std::unordered_map<std::string, int> path_to_size = get_path_to_size(input);

		return ranges::accumulate(path_to_size, 0, ranges::plus(),
			[](auto&& i)
			{
				if (i.second <= 100'000)
				{
					return i.second;
				}
				else
				{
					return 0;
				}
			});
	}

	int part2(const puzzle_input& input)
	{
		std::unordered_map<std::string, int> path_to_size = get_path_to_size(input);

		int free = 70'000'000 - path_to_size["/"];
		int additional_required = 30'000'000 - free;
		auto sorted = path_to_size | ranges::views::values | ranges::to<std::vector> | ranges::actions::sort;
		return *ranges::lower_bound(sorted, additional_required);
	}
}
