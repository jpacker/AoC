#include "day1.h"

#include <charconv>
#include <limits>

namespace
{
	template <unsigned WindowSize>
	unsigned NumIncreasesSlidingWindow_(std::string_view input)
	{
		constexpr auto buffSize = WindowSize + 1;
		unsigned buff[buffSize];
		unsigned sum = 0;
		
		unsigned numIncreases = 0;

		const auto endPtr = input.data() + input.size();

		unsigned depth;
		auto parseRes = std::from_chars(input.data(), endPtr, depth);
		for (unsigned i = 0; i < WindowSize && parseRes.ec != std::errc::invalid_argument; ++i)
		{
			buff[i] = depth;
			sum += depth;
			parseRes = std::from_chars(parseRes.ptr + 1, endPtr, depth);
		}
		unsigned previousSum = sum;

		while (parseRes.ec != std::errc::invalid_argument)
		{
			sum += depth;
			sum -= buff[0];
			if (sum > previousSum)
			{
				++numIncreases;
			}

			buff[WindowSize] = depth;
			previousSum = sum;

			for (unsigned i = 1; i < buffSize; ++i)
			{
				buff[i - 1] = buff[i];
			}
			parseRes = std::from_chars(parseRes.ptr + 1, endPtr, depth);
		}

		return numIncreases;
	}
}

Solution day1(std::string_view input)
{
	Solution sol;

	// Idea... iterate just once.. does it make it faster? It will be less clear

	sol.part1 = NumIncreasesSlidingWindow_<1>(input);
	sol.part2 = NumIncreasesSlidingWindow_<3>(input);

	return sol;
}
