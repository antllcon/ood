#pragma once
#include "InputDataStreamDecorator.h"

class DecompressInputStream final : public InputDataStreamDecorator
{
public:
	explicit DecompressInputStream(InStreamPtr&& wrappedStream)
		: InputDataStreamDecorator(std::move(wrappedStream))
	{
	}

	uint8_t ReadByte() override
	{
		if (m_chunkCount == 0)
		{
			if (!LoadChunk())
			{
				throw std::ios_base::failure("Attempt to read past EOF (decompression)");
			}
		}

		--m_chunkCount;
		return m_currentByte;
	}

	// TODO: проверить
	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override
	{
		{
			auto pBuffer = static_cast<uint8_t*>(dstBuffer);
			std::streamsize bytesRead = 0;

			try
			{
				for (bytesRead = 0; bytesRead < size; ++bytesRead)
				{
					pBuffer[bytesRead] = ReadByte();
				}
			}
			catch (const std::ios_base::failure& e)
			{
			}

			return bytesRead;
		}
	}

private:
	bool LoadChunk()
	{
		try
		{
			const uint8_t count = m_wrappedStream->ReadByte();
			const uint8_t byte = m_wrappedStream->ReadByte();

			m_chunkCount = count;
			m_currentByte = byte;
			return true;
		}
		catch (const std::ios_base::failure& e)
		{
			if (m_wrappedStream->IsEOF())
			{
				return false;
			}

			throw;
		}
	}

	uint8_t m_chunkCount = 0;
	uint8_t m_currentByte = 0;
};