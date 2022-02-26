#include "day1.h"

#include <charconv>
#include <limits>

namespace
{
	class Aggregator3
	{
	public:

		void Add(unsigned value)
		{
			vals_[index] = value;
			aggregate_ += value;
			++index;
			if (index >= 3)
			{
				index = 0;
			}
		}

		void Evict()
		{
			aggregate_ -= vals_[index];
		}

		unsigned Aggregate() const
		{
			return aggregate_;
		}

	private:
		int index = 0;
		unsigned vals_[3] = {0};
		unsigned aggregate_ = 0;
	};
}

Solution day1(std::string_view input)
{
	Solution sol;

	unsigned previousDepth = 0;
	unsigned currentDepth = 0;
	unsigned prev3 = std::numeric_limits<unsigned>::max();

	sol.part1 = 0;

	int i = 0;
	Aggregator3 agg;
	
	auto parseRes = std::from_chars(input.data(), input.data() + input.size(), previousDepth);
	currentDepth = previousDepth;
	while (parseRes.ec != std::errc::invalid_argument)
	{
		agg.Add(currentDepth);
		++i;
		if (i >= 3)
		{
			auto currWindowSum = agg.Aggregate();
			agg.Evict();

			if (currWindowSum > prev3)
			{
				++sol.part2;
			}
			prev3 = currWindowSum;
		}

		if (currentDepth > previousDepth)
		{
			++sol.part1;
		}
		previousDepth = currentDepth;
		parseRes = std::from_chars(parseRes.ptr + 1, input.data() + input.size(), currentDepth);
	}


	return sol;
}