#pragma once
#include <string>

class IParagraph
{
public:
	virtual ~IParagraph() = default;

	IParagraph(const IParagraph&) = delete;
	IParagraph& operator=(const IParagraph&) = delete;

	virtual const std::string& GetText() const = 0;
	virtual void SetText(const std::string& text) = 0;

protected:
	IParagraph() = default;
};