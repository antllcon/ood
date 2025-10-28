#pragma once
#include <string>

class IParagraph
{
public:
	virtual ~IParagraph() = default;

	virtual const std::string& GetText() const = 0;
	virtual void SetText(const std::string& text) = 0;
};