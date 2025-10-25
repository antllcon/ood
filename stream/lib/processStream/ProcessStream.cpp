#include "ProcessStream.h"
#include "input/DecompressInputStream.h"
#include "input/DecryptInputStream.h"
#include "input/FileInputStream.h"
#include "output/CompressOutputStream.h"
#include "output/EncryptOutputStream.h"
#include "output/FileOutputStream.h"

#include <iomanip>
#include <iostream>
#include <memory>
#include <vector>

namespace ProcessStream
{
void CopyStream(IInputDataStream& input, IOutputDataStream& output)
{
	constexpr std::streamsize BUFFER_SIZE = 4096;
	std::vector<uint8_t> buffer(BUFFER_SIZE);

	while (!input.IsEOF())
	{
		auto readSize = input.ReadBlock(buffer.data(), BUFFER_SIZE);
		if (readSize > 0)
		{
			output.WriteBlock(buffer.data(), readSize);
		}
	}
}

void ProcessTransform(int argc, char* argv[])
{
	if (argc < 3)
	{
		throw std::invalid_argument("Not enough arguments");
	}

	const std::string inputFileName = argv[argc - 2];
	const std::string outputFileName = argv[argc - 1];

	InStreamPtr inputStream = std::make_unique<FileInputStream>(inputFileName);
	OutStreamPtr outputStream = std::make_unique<FileOutputStream>(outputFileName);

	for (int i = 1; i < argc - 2; ++i)
	{
		const std::string opt = argv[i];

		if (opt == "--encrypt" || opt == "--decrypt")
		{
			if (i + 1 >= argc - 2)
			{
				throw std::invalid_argument("Missing key for " + opt);
			}

			const std::string keyStr = argv[++i];
			unsigned long key = 0;
			try
			{
				key = std::stoul(keyStr);
			}
			catch (const std::exception& e)
			{
				(void)e;
				throw std::invalid_argument("Invalid key value: " + keyStr);
			}

			if (opt == "--encrypt")
			{
				outputStream = std::make_unique<EncryptOutputStream>(std::move(outputStream), key);
			}
			else
			{
				inputStream = std::make_unique<DecryptInputStream>(std::move(inputStream), key);
			}
		}
		else if (opt == "--compress")
		{
			outputStream = std::make_unique<CompressOutputStream>(std::move(outputStream));
		}
		else if (opt == "--decompress")
		{
			inputStream = std::make_unique<DecompressInputStream>(std::move(inputStream));
		}
		else
		{
			throw std::invalid_argument("Unknown option: " + opt);
		}
	}

	std::cout << "Transform " << inputFileName << " to " << outputFileName << "..." << std::endl;
	CopyStream(*inputStream, *outputStream);

	outputStream->Close();
}
}