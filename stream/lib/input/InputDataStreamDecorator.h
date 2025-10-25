#pragma once
#include "IInputDataStream.h"

class InputDataStreamDecorator : public IInputDataStream
{
public:
	explicit InputDataStreamDecorator(InStreamPtr&& wrappedStream)
		: m_wrappedStream(std::move(wrappedStream))
	{
	}

	bool IsEOF() const override
	{
		return m_wrappedStream->IsEOF();
	}

	uint8_t ReadByte() override
	{
		return m_wrappedStream->ReadByte();
	}

	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override
	{
		return m_wrappedStream->ReadBlock(dstBuffer, size);
	}

protected:
	InStreamPtr m_wrappedStream;
};