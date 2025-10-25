#pragma once
#include "../cryptUtils/CryptUtils.h"
#include "InputDataStreamDecorator.h"

class DecryptInputStream final : public InputDataStreamDecorator
{
public:
	DecryptInputStream(InStreamPtr&& wrappedStream, unsigned long key)
		: InputDataStreamDecorator(std::move(wrappedStream))
		, m_decryptTable(CryptUtils::GenerateDecryptTable(key))
	{
	}

	uint8_t ReadByte() override
	{
		const uint8_t encryptedByte = m_wrappedStream->ReadByte();
		return DecryptByte(encryptedByte);
	}

	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override
	{
		const std::streamsize readSize = m_wrappedStream->ReadBlock(dstBuffer, size);

		auto pBuffer = static_cast<uint8_t*>(dstBuffer);
		for (std::streamsize i = 0; i < readSize; ++i)
		{
			pBuffer[i] = DecryptByte(pBuffer[i]);
		}

		return readSize;
	}

private:
	uint8_t DecryptByte(uint8_t byte) const
	{
		return m_decryptTable[byte];
	}

	CryptUtils::CryptTable m_decryptTable;
};