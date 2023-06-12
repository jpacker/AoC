#include <array>
#include <chrono>
#include <format>
#include <iostream>
#include <string>

#include "all_days.h"

constexpr std::array days =
{
	&day1, &day2, &day3, &day4, &day5,
};

static std::string DayFilePath(std::size_t day)
{
	return std::format("../../inputs/day{}.txt", day);
}

int main()
{
	for (std::size_t i = 0; i < days.size(); i++)
	{
		const std::string dayFilePath = DayFilePath(i + 1);
		const auto input = SlurpInput(dayFilePath);

		const auto start = std::chrono::steady_clock::now();
		auto sol = days[i](input);
		const auto end = std::chrono::steady_clock::now();

		auto timeInMicroSec = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

		std::cout << "Day " << (i + 1) << ": (" << sol.part1 << ", " << sol.part2 << ") -- " << timeInMicroSec << '\n';
	}
	
	return 0;
}
