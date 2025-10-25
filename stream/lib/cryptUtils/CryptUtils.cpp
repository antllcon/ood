#include "CryptUtils.h"
#include <algorithm>
#include <numeric>
#include <random>

namespace CryptUtils
{
static CryptTable CreateShuffledTable(unsigned long key)
{
	CryptTable table(TABLE_SIZE);

	std::iota(table.begin(), table.end(), 0);
	std::mt19937 randomGenerator(key);
	std::ranges::shuffle(table, randomGenerator);

	return table;
}

CryptTable GenerateEncryptTable(unsigned long key)
{
	return CreateShuffledTable(key);
}

CryptTable GenerateDecryptTable(unsigned long key)
{
	const CryptTable encryptTable = CreateShuffledTable(key);
	CryptTable decryptTable(TABLE_SIZE);

	for (size_t i = 0; i < TABLE_SIZE; ++i)
	{
		decryptTable[encryptTable[i]] = static_cast<uint8_t>(i);
	}

	return decryptTable;
}
} // namespace CryptUtils