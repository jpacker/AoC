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
			return countOnes >= countZeros ? Bit::One : Bit::Zero;
		}

		char LeastCommonChar() const
		{
			return countOnes < countZeros ? '1' : '0';
		}

		char MostCommonChar() const
		{
			return countOnes >= countZeros ? '1' : '0';
		}

		void Reset()
		{
			countOnes = countZeros = 0;
		}

		unsigned countOnes = 0;
		unsigned countZeros = 0;
	};

	unsigned BinaryStringToDec_(const std::string_view& str)
	{
		unsigned i = 0;
		unsigned num = 0;

		for (auto it = str.rbegin(), end = str.rend(); it != end; ++it)
		{
			num += static_cast<unsigned>(*it == '1') << i;
			++i;
		}

		return num;
	}

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

	std::vector<std::string_view> ParsedInput_(std::string_view input)
	{
		std::vector<std::string_view> nums;
		nums.reserve(1000);
		const auto numColumns = input.find('\n');	// assume all lines are the same length
		auto ptr = input.data();
		const auto endPtr = input.data() + input.size();
		while (ptr < endPtr)
		{
			nums.emplace_back(ptr, numColumns);
			ptr += numColumns + 1;
		} 
		return nums;
	}



	void UpdateAllColumnCounts_(
		std::vector<ColumnCounts>& columns, 
		std::vector<std::string_view>::iterator itNumbers,
		const std::vector<std::string_view>::iterator itNumbersEnd
	)
	{
		const auto numColumns = itNumbers->length();
		for (; itNumbers != itNumbersEnd; ++itNumbers)
		{
			for (std::size_t i = 0; i < numColumns; ++i)
			{
				columns[i].countOnes += (*itNumbers)[i] != '0';
				columns[i].countZeros += (*itNumbers)[i] == '0';
			}
		}
	}

	void UpdateSpecificColumnCountForAllWords_(
		ColumnCounts& column,
		std::size_t columnNum,
		std::vector<std::string_view>::iterator itNumbers,
		const std::vector<std::string_view>::iterator itNumbersEnd
	)
	{
		for (; itNumbers != itNumbersEnd; ++itNumbers)
		{
			column.countOnes += (*itNumbers)[columnNum] != '0';
			column.countZeros += (*itNumbers)[columnNum] == '0';
		}
	}

	template <typename FnFilter>
	std::string_view FilteredNumber_(
		std::vector<ColumnCounts>& columns,
		const std::vector<std::string_view>::iterator itNumbersBegin,
		std::vector<std::string_view>::iterator itNumbersEnd,
		FnFilter fn
	)
	{
		itNumbersEnd = std::remove_if(itNumbersBegin, itNumbersEnd, [&](const auto& s) {return fn(s[0], columns[0]); });
		int i = 1;
		while (itNumbersEnd - itNumbersBegin > 1)
		{
			columns[i].Reset();
			UpdateSpecificColumnCountForAllWords_(columns[i], i, itNumbersBegin, itNumbersEnd);
			itNumbersEnd = std::remove_if(itNumbersBegin, itNumbersEnd, [&](const auto& s) {return fn(s[i], columns[i]); });
			++i;
		}
		return *itNumbersBegin;
	}
}



Solution day3(std::string_view input)
{
	Solution sol;

	std::vector<std::string_view> oxygenNumbers = ParsedInput_(input);

	const auto numColumns = oxygenNumbers.front().length();	// assume all lines are the same length
	std::vector<ColumnCounts> columns(numColumns);

	UpdateAllColumnCounts_(columns, oxygenNumbers.begin(), oxygenNumbers.end());
	const auto gamma = Gamma_(columns);
	const auto epsilon = Epsilon_(gamma, columns.size());

	sol.part1 = gamma * epsilon;

	auto co2Numbers = oxygenNumbers;
	auto co2Counts = columns;

	const auto oxygenNumberStr = FilteredNumber_(columns, oxygenNumbers.begin(), oxygenNumbers.end(), [](char c, const ColumnCounts& col) {return c != col.MostCommonChar(); });
	const auto co2NumberStr = FilteredNumber_(co2Counts, co2Numbers.begin(), co2Numbers.end(), [](char c, const ColumnCounts& col) {return c != col.LeastCommonChar(); });
	
	const auto oxygenNumber = BinaryStringToDec_(oxygenNumberStr);
	const auto co2Number = BinaryStringToDec_(co2NumberStr);

	sol.part2 = oxygenNumber * co2Number;

	return sol;
}
