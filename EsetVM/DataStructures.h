#pragma once
#include "stdafx.h"

namespace Core {
	namespace Utils {
		struct EsetVMFileHeader
		{
			char magic[8];
			uint32_t codeSize;
			uint32_t dataSize;
			uint32_t initialDataSize;
		};

		struct EsetVMArguments {
			short regId;
			Enums::MemoryAccessSize size;
			uint64_t value;
			bool isMemoryAddress = false;
		};

		struct EsetAssembly {
			uint64_t address;
			Enums::Instructions instruction;
			std::vector<EsetVMArguments> arguments;
		};
	}
}