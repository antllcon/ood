#pragma once

#include <memory>

class IInputDataStream
{
public:
	virtual bool IsEOF() const = 0;
	virtual uint8_t ReadByte() = 0;
	virtual std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) = 0;
	virtual ~IInputDataStream() = default;
};

using InStreamPtr = std::unique_ptr<IInputDataStream>;