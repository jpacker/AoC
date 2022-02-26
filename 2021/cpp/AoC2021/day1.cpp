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

		unsigned depth;
		auto parseRes = std::from_chars(input.data(), input.data() + input.size(), depth);
		for (unsigned i = 0; i < WindowSize && parseRes.ec != std::errc::invalid_argument; ++i)
		{
			buff[i] = depth;
			sum += depth;
			parseRes = std::from_chars(parseRes.ptr + 1, input.data() + input.size(), depth);
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
			parseRes = std::from_chars(parseRes.ptr + 1, input.data() + input.size(), depth);
		}

		return numIncreases;
	}
}

Solution day1(std::string_view input)
{
	Solution sol;

	sol.part1 = NumIncreasesSlidingWindow_<1>(input);
	sol.part2 = NumIncreasesSlidingWindow_<3>(input);

	return sol;
}