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

	class StatePartOne
	{
	public:
		void Down(unsigned val)
		{
			depth_ += val;
		}

		void Up(unsigned val)
		{
			depth_ -= val;
		}

		void Forward(unsigned val)
		{
			horizontal_ += val;
		}

		unsigned Result() const
		{
			return horizontal_ * depth_;
		}

	private:
		unsigned depth_ = 0;
		unsigned horizontal_ = 0;
	};

	class StatePartTwo
	{
	public:
		void Down(unsigned val)
		{
			aim_ += val;
		}

		void Up(unsigned val)
		{
			aim_ -= val;
		}

		void Forward(unsigned val)
		{
			horizontal_ += val;
			depth_ += aim_ * val;
		}

		unsigned Result() const
		{
			return horizontal_ * depth_;
		}
	private:
		unsigned depth_ = 0;
		unsigned horizontal_ = 0;
		int aim_ = 0;
	};
}

Solution day2(std::string_view input)
{
	using namespace std::string_view_literals;
	StatePartOne s;
	StatePartTwo s2;
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
				skip = "forward "sv.size();
				break;
			case 'd':
				dir = Direction::Down;
				skip = "down "sv.size();
				break;
			case 'u':
				dir = Direction::Up;
				skip = "up "sv.size();
				break;
			}
			if (skip == 0)
			{
				break;
			}

			inputPtr += skip;

			// 2x faster but assumes single digit input.. perhaps write our own from_chars and avoid the divide
			//unsigned amount = *inputPtr - '0';	
			//inputPtr += 2;
			
			unsigned amount;
			auto parseRes = std::from_chars(inputPtr, endPtr, amount);	// assume valid input
			inputPtr = parseRes.ptr + 1;	// next line

			switch (dir)
			{
			case Direction::Forward:
				s.Forward(amount);
				s2.Forward(amount);
				break;
			case Direction::Down:
				s.Down(amount);
				s2.Down(amount);
				break;
			case Direction::Up:
				s.Up(amount);
				s2.Up(amount);
				break;
			}
		}
	}
	Solution sol;
	sol.part1 = s.Result();
	sol.part2 = s2.Result();
	return sol;
}