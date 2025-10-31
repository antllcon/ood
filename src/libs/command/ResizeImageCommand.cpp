#include "ResizeImageCommand.h"

ResizeImageCommand::ResizeImageCommand(std::shared_ptr<IImage> image, unsigned int newWidth, unsigned int newHeight)
	: m_image(std::move(image))
	, m_newWidth(newWidth)
	, m_newHeight(newHeight)
	, m_oldWidth(0)
	, m_oldHeight(0)
{
}

void ResizeImageCommand::DoExecute()
{
	if (!m_isExecuted)
	{
		m_oldWidth = m_image->GetWidth();
		m_oldHeight = m_image->GetHeight();
	}

	m_image->Resize(m_newWidth, m_newHeight);
}

void ResizeImageCommand::DoUnexecute()
{
	m_image->Resize(m_oldWidth, m_oldHeight);
}

bool ResizeImageCommand::TryToMerge(const ICommand& nextCommand)
{
	if (const auto* other = dynamic_cast<const ResizeImageCommand*>(&nextCommand))
	{
		if (other->m_image == m_image)
		{
			m_newWidth = other->m_newWidth;
			m_newHeight = other->m_newHeight;
			return true;
		}
	}

	return false;
}