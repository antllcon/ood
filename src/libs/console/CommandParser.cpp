#include "CommandParser.h"
#include <sstream>

std::vector<std::string> CommandParser::Tokenize(const std::string& input)
{
	std::vector<std::string> tokens;
	std::stringstream ss(input);
	std::string token;

	while (ss >> token)
	{
		tokens.push_back(token);
	}
	return tokens;
}

std::string CommandParser::Join(const std::vector<std::string>& tokens, size_t startIndex)
{
	if (startIndex >= tokens.size())
	{
		return "";
	}

	std::ostringstream oss;
	oss << tokens[startIndex];
	for (size_t i = startIndex + 1; i < tokens.size(); ++i)
	{
		oss << " " << tokens[i];
	}

	return oss.str();
}

std::optional<size_t> CommandParser::ParsePosition(const std::string& posStr, size_t maxItems)
{
	if (posStr == "end")
	{
		return std::nullopt;
	}

	size_t pos = std::stoul(posStr);

	if (pos > maxItems)
	{
		throw std::out_of_range(
			"Invalid position. Index '" + posStr + "' is out of bounds [0, "
			+ std::to_string(maxItems) + "].");
	}

	return pos;
}

std::pair<unsigned int, unsigned int> CommandParser::ParseDimensions(const std::string& widthStr, const std::string& heightStr)
{
	unsigned int width = std::stoul(widthStr);
	unsigned int height = std::stoul(heightStr);

	if (width < MIN_DIMENSION || width > MAX_DIMENSION || height < MIN_DIMENSION || height > MAX_DIMENSION)
	{
		throw std::out_of_range(
			"Invalid dimensions. Size must be in range ["
			+ std::to_string(MIN_DIMENSION) + ", "
			+ std::to_string(MAX_DIMENSION) + "].");
	}

	return { width, height };
}