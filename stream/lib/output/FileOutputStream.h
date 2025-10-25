#pragma once
#include "IOutputDataStream.h"

#include <fstream>
#include <ios>
#include <string>

class FileOutputStream final : public IOutputDataStream
{
public:
	explicit FileOutputStream(const std::string& fileName)
	{
		m_stream.open(fileName, std::ios::binary | std::ios::trunc);

		if (!m_stream.is_open())
		{
			throw std::ios_base::failure("Failed to open output file: " + fileName);
		}
	}

	~FileOutputStream() override
	{
		Close();
	}

	void WriteByte(uint8_t data) override
	{
		CheckIfClosed();
		m_stream.put(static_cast<char>(data));

		if (m_stream.fail())
		{
			throw std::ios_base::failure("Failed to write byte to file");
		}
	}

	void WriteBlock(const void* srcData, std::streamsize size) override
	{
		CheckIfClosed();
		const auto pSrc = static_cast<const char*>(srcData);

		m_stream.write(pSrc, size);

		if (m_stream.fail())
		{
			throw std::ios_base::failure("Failed to write block to file");
		}
	}

	void Close() override
	{
		if (m_isClosed)
		{
			return;
		}

		m_stream.close();
		m_isClosed = true;
	}

private:
	void CheckIfClosed() const
	{
		if (m_isClosed)
		{
			throw std::logic_error("Attempt to write to a closed stream");
		}
	}

	std::ofstream m_stream;
	bool m_isClosed = false;
};