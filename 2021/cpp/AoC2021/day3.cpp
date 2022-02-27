#include "day3.h"

#include <cassert>
#include <vector>

namespace
{
	enum class Bit
	{
		Zero,
		One,
	};

	class ColumnCounts
	{
	public:
		Bit MostCommon() const
		{
			return countOnes > countZeros ? Bit::One : Bit::Zero;
		}

		unsigned countOnes = 0;
		unsigned countZeros = 0;
	};

	unsigned Gamma_(const std::vector<ColumnCounts>& columns)
	{
		unsigned i = 0;
		unsigned gamma = 0;

		for (auto it = columns.rbegin(), end = columns.rend(); it != end; ++it)
		{
			gamma += static_cast<unsigned>(it->MostCommon() == Bit::One) << i;
			++i;
		}

		return gamma;
	}

	constexpr unsigned Mask_(unsigned numOneBits)
	{
		assert(numOneBits < 32);
		return (1u << numOneBits) - 1;
	}

	unsigned Epsilon_(unsigned gamma, std::size_t numColumns)
	{
		return ~gamma & Mask_(numColumns);
	}
}



Solution day3(std::string_view input)
{
	Solution sol;

	const auto endIt = input.end();
	auto it = input.begin();

	auto posNewLine = input.find('\n');	
	const auto numColumns = posNewLine;	// assume all lines are the same length
	std::vector<ColumnCounts> columns(numColumns);

	while (it < endIt)
	{
		for (auto& column : columns)
		{
			column.countOnes += *it != '0';
			column.countZeros += *it == '0';
			++it;
		}
		if (it != endIt)
		{
			++it;
		}
	}

	const auto gamma = Gamma_(columns);
	const auto epsilon = Epsilon_(gamma, columns.size());

	sol.part1 = gamma * epsilon;

	return sol;
}
