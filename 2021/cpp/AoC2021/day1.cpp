#include "day1.h"
#include <charconv>

Solution day1(std::string_view input)
{
	Solution sol;

	unsigned previousDepth = 0;
	unsigned currentDepth = 0;

	sol.part1 = 0;
	
	auto parseRes = std::from_chars(input.data(), input.data() + input.size(), previousDepth);
	currentDepth = previousDepth;
	while (parseRes.ec != std::errc::invalid_argument)
	{
		if (currentDepth > previousDepth)
		{
			++sol.part1;
		}
		previousDepth = currentDepth;
		parseRes = std::from_chars(parseRes.ptr + 1, input.data() + input.size(), currentDepth);
	}


	return sol;
}