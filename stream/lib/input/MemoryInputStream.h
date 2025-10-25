#pragma once
#include "IInputDataStream.h"

#include <ios>
#include <vector>
#include <algorithm>
#include <stdexcept>

class MemoryInputStream final : public IInputDataStream
{
public:
	explicit MemoryInputStream(const std::vector<uint8_t>& data)
		: m_data(data)
	{
	}

	bool IsEOF() const override
	{
		return m_pos >= m_data.size();
	}

	uint8_t ReadByte() override
	{
		if (IsEOF())
		{
			throw std::ios_base::failure("Attempt to read past EOF");
		}

		return m_data[m_pos++];
	}

	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override
	{
		auto pDst = static_cast<uint8_t*>(dstBuffer);

		const std::streamsize remainingSize = m_data.size() - m_pos;
		const std::streamsize bytesToRead = std::min(size, remainingSize);

		std::copy_n(m_data.begin() + m_pos, bytesToRead, pDst);
		m_pos += bytesToRead;

		return bytesToRead;
	}

private:
	const std::vector<uint8_t>& m_data;
	size_t m_pos = 0;
};