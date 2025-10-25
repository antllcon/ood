#pragma once
#include "../cryptUtils/CryptUtils.h"
#include "OutputDataStreamDecorator.h"

#include <vector>

class EncryptOutputStream final : public OutputDataStreamDecorator
{
public:
	EncryptOutputStream(OutStreamPtr&& wrappedStream, unsigned long key)
		: OutputDataStreamDecorator(std::move(wrappedStream))
		, m_encryptTable(CryptUtils::GenerateEncryptTable(key))
	{
	}

	void WriteByte(uint8_t data) override
	{
		const uint8_t encryptedByte = EncryptByte(data);
		m_wrappedStream->WriteByte(encryptedByte);
	}

	void WriteBlock(const void* srcData, std::streamsize size) override
	{
		std::vector<uint8_t> encryptedBlock(size);
		const auto pSrc = static_cast<const uint8_t*>(srcData);

		for (std::streamsize i = 0; i < size; ++i)
		{
			encryptedBlock[i] = EncryptByte(pSrc[i]);
		}

		m_wrappedStream->WriteBlock(encryptedBlock.data(), size);
	}

private:
	uint8_t EncryptByte(uint8_t byte) const
	{
		return m_encryptTable[byte];
	}

	CryptUtils::CryptTable m_encryptTable;
};