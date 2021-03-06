#include "stdafx.h"

using namespace Core;
using namespace Core::Utils;

int main(int argc, char *argv[])
{
	char* filePathBuffer = new char[255];

#ifdef _DEBUG
	//filePathBuffer = (char*)"C:/Users/patry/Desktop/EsetVM/x64/Debug/vm-files/math.evm";
	//filePathBuffer = (char*)"C:/Users/patry/Desktop/EsetVM/x64/Debug/vm-files/memory.evm";
	//filePathBuffer = (char*)"C:/Users/patry/Desktop/EsetVM/x64/Debug/vm-files/fibonacci_loop.evm";
    filePathBuffer = (char*)"C:/Users/patry/Desktop/EsetVM/x64/Debug/vm-files/xor.evm";
#endif

	if (argc > 1) {
		filePathBuffer = argv[1];
	}

	VMCore* vm = new VMCore();
	Validator* validator = new Validator(filePathBuffer);
	if (validator->fileIsValid) {
		Loader* loader = new Loader(validator->opcode, vm);
		vm->MemoryDump();
		vm->Run();
	}

	system("PAUSE");

    return 0;
}