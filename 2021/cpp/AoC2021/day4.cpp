#include "day4.h"

#include <algorithm>
#include <array>
#include <cassert>
#include <charconv>
#include <numeric>
#include <vector>


namespace
{
	inline bool ascii_isspace(char c) 
	{ 
		// TODO: Could replace this with lookup table a la absl::ascii_isspace
		return c == ' ' || (c >= '\t' && c <= '\r'); 
	}

	inline std::string_view StripLeadingAsciiWhitespace_(std::string_view str) 
	{
		auto it = std::find_if_not(str.begin(), str.end(), ascii_isspace);
		return str.substr(static_cast<size_t>(it - str.begin()));
	}

	using Calls = std::vector<int>;
	using Board = std::array<int, 25>;		

	Calls ParseCalls_(std::string_view callsView)
	{
		const auto numEntries = std::count(callsView.begin(), callsView.end(), ',') + 1;
		Calls calls(numEntries, -1);
		
		{
			const auto endPtr = callsView.data() + callsView.size();
			auto beginPtr = callsView.data();

			for (int i = 0; i < numEntries; ++i)
			{
				int call = -1;
				auto parseRes = std::from_chars(beginPtr, endPtr, call);
				assert(parseRes.ec != std::errc::invalid_argument);
				calls[i] = call;
				beginPtr = parseRes.ptr + 1;
			}
		}

		return calls;
	}

	struct BoardState
	{
		int lastCallIndex = -1;
		int calledSum = 0;
		Board board;
	};

	std::string_view ParseSingleBoard_(BoardState& state, std::string_view remainingInput)
	{
		state = BoardState();
		state.board.fill(-1);
		auto beginPtr = remainingInput.data();
		const auto endPtr = remainingInput.data() + remainingInput.size();
		for (int i = 0; i < std::ssize(state.board) && beginPtr != endPtr; ++i)
		{
			beginPtr = StripLeadingAsciiWhitespace_(std::string_view(beginPtr, endPtr)).data();
			int call = -1;
			auto parseRes = std::from_chars(beginPtr, endPtr, call);
			if (parseRes.ec == std::errc::invalid_argument)
			{
				return std::string_view();
			}
			state.board[i] = call;
			beginPtr = parseRes.ptr;
		}

		return remainingInput.substr(std::distance(remainingInput.data(), beginPtr));
	}

	void ProcessCall_(BoardState& state, int call)
	{
		if (auto it = std::ranges::find(state.board, call); it != state.board.end())
		{
			state.calledSum += call;
			*it = -1;
		}
	}

	int BoardSum_(const Board& board)
	{
		return std::accumulate(board.begin(), board.end(), 0);
	}

	bool IsBoardWin_(const Board& board)
	{
		// Check the rows for a win
		for (int i = 0; i < 5; ++i)
		{
			bool isWin = true;
			for (int j = 0; isWin && j < 5; ++j)
			{
				isWin = isWin && board[i * 5 + j] == -1;
			}
			if (isWin)
			{
				return true;
			}
		}

		// Check the columns for a win
		for (int i = 0; i < 5; ++i)
		{
			bool isWin = true;
			for (int j = 0; isWin && j < 5; ++j)
			{
				isWin = isWin && board[j * 5 + i] == -1;
			}
			if (isWin)
			{
				return true;
			}
		}

		return false;
	}
}

Solution day4(std::string_view input)
{
	const auto charsInFirstLine = input.find('\n');
	const Calls calls = ParseCalls_(input.substr(0, charsInFirstLine));
	BoardState state;

	int firstToWinBoardScore = 0;
	int firstToWinLastCallIndex = std::numeric_limits<int>::max();
	int lastToWinBoardScore = 0;
	int lastToWinLastCallIndex = std::numeric_limits<int>::min();

	auto remainingInput = ParseSingleBoard_(state, input.substr(charsInFirstLine));
	while(state.board[0] != -1)
	{
		const auto boardSum = BoardSum_(state.board);
		for (int i = 0; i < std::ssize(calls); ++i)
		{
			ProcessCall_(state, calls[i]);
			state.lastCallIndex = i;
			const auto boardScore = boardSum - state.calledSum;
			if (boardScore < 0)
			{
				break;
			}
			if (IsBoardWin_(state.board))
			{
				if (i < firstToWinLastCallIndex)
				{
					firstToWinBoardScore = boardScore;
					firstToWinLastCallIndex = i;
				}
				if (i > lastToWinLastCallIndex)
				{
					lastToWinBoardScore = boardScore;
					lastToWinLastCallIndex = i;
				}
				break;
			}
		}
		
		remainingInput = ParseSingleBoard_(state, remainingInput);
	} 

	Solution sol;
	sol.part1 = firstToWinBoardScore * calls[firstToWinLastCallIndex];
	sol.part2 = lastToWinBoardScore * calls[lastToWinLastCallIndex];
	return sol;
}