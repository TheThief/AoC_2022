#pragma once

#include <unordered_map>
#include <variant>
#include <vector>

#include <range/v3/all.hpp>
#include "stream_required.h"
#include "delimitered.h"

namespace aoc2022::day11
{
	struct monkey
	{
		std::vector<int64_t> items;
		char operation;
		int value;
		int test_value;
		int monkey_if_true;
		int monkey_if_false;

		friend std::istream& operator>>(std::istream& is, monkey& input)
		{
			int m;
			is >> required{ "Monkey " } >> m >> required{ ":" };
			delimitered_vector<int64_t, ','> items;
			is >> required{ "Starting items: " } >> items;
			input.items = std::move(items.value);
			is >> required{ "Operation: new = old " } >> input.operation >> std::ws;
			if (is.peek() == 'o')
			{
				is >> required{ "old" };
				input.operation = '^';
				input.value = 2;
			}
			else
			{
				is >> input.value;
			}
			is >> required{ "Test: divisible by " } >> input.test_value;
			is >> required{ "If true: throw to monkey " } >> input.monkey_if_true;
			is >> required{ "If false: throw to monkey " } >> input.monkey_if_false;

			return is;
		}
	};


	struct puzzle_input
	{
		std::vector<monkey> monkeys;

		friend std::istream& operator>>(std::istream& is, puzzle_input& input)
		{
			input.monkeys = ranges::istream_view<monkey>(is) | ranges::to<std::vector>;

			return is;
		}
	};

	struct live_monkey : monkey
	{
		live_monkey(const monkey& base) noexcept
			: monkey(base)
		{}

		int inspected = 0;
	};

	int part1(const puzzle_input& input)
	{
		std::vector<live_monkey> monkeys = input.monkeys | ranges::to<std::vector<live_monkey>>;
		for (int round = 0; round < 20; ++round)
		{
			for (auto& m : monkeys)
			{
				for (auto&& i : m.items)
				{
					if (m.operation == '+')
						i += m.value;
					if (m.operation == '*')
						i *= m.value;
					if (m.operation == '^')
						i *= i;
					i /= 3;
					if (i % m.test_value == 0)
						monkeys[m.monkey_if_true].items.push_back(i);
					else
						monkeys[m.monkey_if_false].items.push_back(i);
				}
				m.inspected += m.items.size();
				m.items.clear();
			}
		}
		ranges::partial_sort(monkeys, monkeys.begin() + 2, ranges::greater(), &live_monkey::inspected);
		return monkeys[0].inspected * monkeys[1].inspected;
	}

	int64_t part2(const puzzle_input& input)
	{
		int modulus = ranges::accumulate(input.monkeys, 1, ranges::multiplies(), &monkey::test_value);
		std::vector<live_monkey> monkeys = input.monkeys | ranges::to<std::vector<live_monkey>>;
		for (int round = 0; round < 10000; ++round)
		{
			for (auto& m : monkeys)
			{
				for (auto&& i : m.items)
				{
					if (m.operation == '+')
						i += m.value;
					if (m.operation == '*')
						i *= m.value;
					if (m.operation == '^')
						i *= i;
					i %= modulus;
					if (i % m.test_value == 0)
						monkeys[m.monkey_if_true].items.push_back(i);
					else
						monkeys[m.monkey_if_false].items.push_back(i);
				}
				m.inspected += m.items.size();
				m.items.clear();
			}
		}
		ranges::partial_sort(monkeys, monkeys.begin() + 2, ranges::greater(), &live_monkey::inspected);
		return (int64_t)monkeys[0].inspected * monkeys[1].inspected;
	}
}
