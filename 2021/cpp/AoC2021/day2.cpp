#include "day2.h"

#include <cassert>
#include <charconv>

namespace
{
	enum class Direction
	{
		Up,
		Down,
		Forward,
	};

	struct State
	{
		unsigned depth = 0;
		unsigned horizontal = 0;
	};
}

Solution day2(std::string_view input)
{
	using namespace std::string_view_literals;
	Solution sol;
	State s;
	auto inputPtr = input.data();
	if (input.size())
	{
		const auto endPtr = input.data() + input.size();
		while (inputPtr < endPtr)
		{
			int skip = 0;
			Direction dir;
			switch (*inputPtr)
			{
			case 'f':
				dir = Direction::Forward;
				skip = "forward"sv.size();
				break;
			case 'd':
				dir = Direction::Down;
				skip = "down"sv.size();
				break;
			case 'u':
				dir = Direction::Up;
				skip = "up"sv.size();
				break;
			}
			if (skip == 0)
			{
				break;
			}
			++skip;	// space

			inputPtr += skip;

			unsigned amount = 0;
			auto parseRes = std::from_chars(inputPtr, endPtr, amount);
			inputPtr = parseRes.ptr + 1;	// next line

			switch (dir)
			{
			case Direction::Forward:
				s.horizontal += amount;
				break;
			case Direction::Down:
				s.depth += amount;
				break;
			case Direction::Up:
				s.depth -= amount;
				break;
			}
		}
	}

	sol.part1 = s.depth * s.horizontal;
	return sol;
}