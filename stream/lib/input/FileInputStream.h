#pragma once
#include "IInputDataStream.h"
#include <string>
#include <fstream>
#include <ios>

class FileInputStream final : public IInputDataStream
{
public:
	explicit FileInputStream(const std::string& fileName)
	{
		m_stream.open(fileName, std::ios::binary);

		if (!m_stream.is_open())
		{
			throw std::ios_base::failure("Failed to open input file: " + fileName);
		}
	}

	bool IsEOF() const override
	{
		return m_stream.peek() == EOF;
	}

	uint8_t ReadByte() override
	{
		int byte = m_stream.get();
		if (byte == EOF)
		{
			if (m_stream.eof())
			{
				throw std::ios_base::failure("Attempt to read past EOF");
			}

			throw std::ios_base::failure("Failed to read byte from file");
		}

		return static_cast<uint8_t>(byte);
	}

	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override
	{
		auto pDst = static_cast<char*>(dstBuffer);
		m_stream.read(pDst, size);

		if (m_stream.fail() && !m_stream.eof())
		{
			throw std::ios_base::failure("Failed to read block from file");
		}

		return m_stream.gcount();
	}

private:
	mutable std::ifstream m_stream;
};