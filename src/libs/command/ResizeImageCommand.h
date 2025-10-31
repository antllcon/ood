#pragma once
#include "ICommand.h"
#include "image/IImage.h"

class ResizeImageCommand final : public ICommand
{
public:
	explicit ResizeImageCommand(std::shared_ptr<IImage> image, unsigned int newWidth, unsigned int newHeight);

	void Execute() override;
	void Unexecute() override;
	bool TryToMerge(const ICommand& nextCommand) override;

private:
	std::shared_ptr<IImage> m_image;
	unsigned int m_newWidth, m_newHeight;
	unsigned int m_oldWidth, m_oldHeight;
	bool m_executedOnce = false;
};