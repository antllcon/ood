#pragma once

#include "IParagraph.h"

class Paragraph final : public IParagraph
{
public:
	explicit Paragraph(const std::string& text);
	~Paragraph() override = default;

	const std::string& GetText() const override;
	void SetText(const std::string& text) override;

private:
	std::string m_text;
};