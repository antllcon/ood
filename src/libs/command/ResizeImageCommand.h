#pragma once
#include "ICommand.h"
#include "image/IImage.h"

class ResizeImageCommand final : public ICommand
{
public:
	explicit ResizeImageCommand(std::shared_ptr<IImage> image, unsigned int newWidth, unsigned int newHeight);
	~ResizeImageCommand() override = default;

	bool TryToMerge(const ICommand& nextCommand) override;

protected:
	void DoExecute() override;
	void DoUnexecute() override;

private:
	std::shared_ptr<IImage> m_image;
	unsigned int m_newWidth, m_newHeight;
	unsigned int m_oldWidth, m_oldHeight;
};