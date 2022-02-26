#include <array>
#include <chrono>
#include <iostream>

#include "all_days.h"

constexpr std::array days =
{
	&day1,
};

constexpr std::array dayStrings =
{
	"day1",
};

static_assert(dayStrings.size() == days.size(), "Forgot to add a day?");

std::string DayFilePath(std::string_view dayStr)
{
	return std::string("../../inputs/") + dayStr.data() + ".txt";
}

int main()
{
	for (std::size_t i = 0; i < days.size(); i++)
	{
		const std::string dayFilePath = DayFilePath(dayStrings[i]);
		const auto input = SlurpInput(dayFilePath);

		const auto start = std::chrono::high_resolution_clock::now();
		auto sol = days[i](input);
		const auto end = std::chrono::high_resolution_clock::now();

		auto timeInMicroSec = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

		std::cout << "Day 1: (" << sol.part1 << ", " << sol.part2 << ") -- " << timeInMicroSec << '\n';
	}
	
	return 0;
}