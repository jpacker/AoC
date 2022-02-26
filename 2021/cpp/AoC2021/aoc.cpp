#include "aoc.h"

#include <fstream>
#include <filesystem>

std::string SlurpInput(std::string_view fileName)
{
	std::filesystem::path p(fileName);
	auto fileSize = std::filesystem::file_size(p);
	std::string contents(fileSize, ' ');
	std::ifstream file(p);
	file.read(contents.data(), fileSize);
	return contents;
}