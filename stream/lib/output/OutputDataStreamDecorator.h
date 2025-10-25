#pragma once
#include "IOutputDataStream.h"

class OutputDataStreamDecorator : public IOutputDataStream
{
public:
	explicit OutputDataStreamDecorator(OutStreamPtr&& wrappedStream)
		: m_wrappedStream(std::move(wrappedStream))
	{
	}

	void WriteByte(uint8_t data) override
	{
		m_wrappedStream->WriteByte(data);
	}

	void WriteBlock(const void* srcData, std::streamsize size) override
	{
		m_wrappedStream->WriteBlock(srcData, size);
	}

	void Close() override
	{
		m_wrappedStream->Close();
	}

protected:
	OutStreamPtr m_wrappedStream;
};