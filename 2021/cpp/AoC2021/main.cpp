#include <array>
#include <chrono>
#include <format>
#include <iostream>
#include <string>

#include "all_days.h"

constexpr std::array days =
{
	&day1, &day2, &day3,
};

static std::string DayFilePath(std::size_t day)
{
#ifdef __clang__
	return std::string("../../inputs/day") + std::to_string(day) + ".txt";
#else
	return std::format("../../inputs/day{}.txt", day);
#endif
}

int main()
{
	for (std::size_t i = 0; i < days.size(); i++)
	{
		const std::string dayFilePath = DayFilePath(i + 1);
		const auto input = SlurpInput(dayFilePath);

		const auto start = std::chrono::high_resolution_clock::now();
		auto sol = days[i](input);
		const auto end = std::chrono::high_resolution_clock::now();

		auto timeInMicroSec = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

		std::cout << "Day " << (i + 1) << ": (" << sol.part1 << ", " << sol.part2 << ") -- " << timeInMicroSec << '\n';
	}
	
	return 0;
}
