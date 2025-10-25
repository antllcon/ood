#pragma once
#include <vector>
#include <cstdint>

namespace CryptUtils
{
static constexpr size_t TABLE_SIZE = 256;
using CryptTable = std::vector<uint8_t>;

CryptTable GenerateEncryptTable(unsigned long key);
CryptTable GenerateDecryptTable(unsigned long key);

} // namespace CryptUtils