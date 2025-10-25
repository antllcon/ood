#pragma once
#include "OutputDataStreamDecorator.h"
#include <stdexcept>

class CompressOutputStream final : public OutputDataStreamDecorator
{
public:
	explicit CompressOutputStream(OutStreamPtr&& wrappedStream)
		: OutputDataStreamDecorator(std::move(wrappedStream))
	{
	}

	void WriteByte(uint8_t data) override
	{
		CheckIfClosed();

		if (m_chunkCount == 0)
		{
			m_lastByte = data;
			m_chunkCount = 1;
			return;
		}

		if (data == m_lastByte)
		{
			if (m_chunkCount == 255)
			{
				FlushChunk();
				m_lastByte = data;
				m_chunkCount = 1;
			}
			else
			{
				++m_chunkCount;
			}
		}
		else
		{
			FlushChunk();
			m_lastByte = data;
			m_chunkCount = 1;
		}
	}

	void WriteBlock(const void* srcData, std::streamsize size) override
	{
		CheckIfClosed();
		const auto pSrc = static_cast<const uint8_t*>(srcData);

		for (std::streamsize i = 0; i < size; ++i)
		{
			WriteByte(pSrc[i]);
		}
	}

	void Close() override
	{
		if (m_isClosed)
		{
			return;
		}

		FlushChunk();
		m_isClosed = true;
		m_wrappedStream->Close();
	}

private:
	void FlushChunk()
	{
		if (m_chunkCount > 0)
		{
			m_wrappedStream->WriteByte(m_chunkCount);
			m_wrappedStream->WriteByte(m_lastByte);
			m_chunkCount = 0;
		}
	}

	void CheckIfClosed() const
	{
		if (m_isClosed)
		{
			throw std::logic_error("Attempt to write to a closed stream");
		}
	}

	uint8_t m_lastByte = 0;
	uint8_t m_chunkCount = 0;
	bool m_isClosed = false;
};