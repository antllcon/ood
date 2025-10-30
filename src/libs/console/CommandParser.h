#pragma once

#include <string>
#include <vector>
#include <optional>
#include <stdexcept>
#include <filesystem>

using Path = std::filesystem::path;

class CommandParser
{
public:
	static std::vector<std::string> Tokenize(const std::string& input);
	static std::string Join(const std::vector<std::string>& tokens, size_t startIndex = 0);
	static std::optional<size_t> ParsePosition(const std::string& posStr, size_t maxItems);
	static std::pair<unsigned int, unsigned int> ParseDimensions(const std::string& widthStr, const std::string& heightStr);

private:
	CommandParser() = default;

	constexpr static unsigned int MIN_DIMENSION = 1;
	constexpr static unsigned int MAX_DIMENSION = 10000;
};