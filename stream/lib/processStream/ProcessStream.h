#pragma once

#include "../input/IInputDataStream.h"
#include "../output/IOutputDataStream.h"

namespace ProcessStream
{
void CopyStream(IInputDataStream& input, IOutputDataStream& output);
void ProcessTransform(int argc, char* argv[]);
}