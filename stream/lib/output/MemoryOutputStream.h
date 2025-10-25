#pragma once
#include "IOutputDataStream.h"
#include <ios>
#include <vector>

class MemoryOutputStream final : public IOutputDataStream
{
public:
	explicit MemoryOutputStream(std::vector<uint8_t>& data)
		: m_data(data)
	{
	}

	void WriteByte(uint8_t data) override
	{
		if (m_isClosed)
		{
			throw std::logic_error("Attempt to write to a closed stream");
		}

		m_data.push_back(data);
	}

	void WriteBlock(const void* srcData, std::streamsize size) override
	{
		if (m_isClosed)
		{
			throw std::logic_error("Attempt to write to a closed stream");
		}

		const auto pSrc = static_cast<const uint8_t*>(srcData);
		m_data.insert(m_data.end(), pSrc, pSrc + size);
	}

	void Close() override
	{
		m_isClosed = true;
	}

private:
	std::vector<uint8_t>& m_data;
	bool m_isClosed = false;
};