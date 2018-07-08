#pragma once

namespace Core {
	class VMCore
	{
	private:
		uint64_t registers[16] = { 0 };
		uint64_t memoryAddress = 0;
		std::vector<Core::Utils::EsetAssembly> memory;
	public:
		VMCore();
		~VMCore();
		void MemoryDump();
		void AddToMemory(Core::Utils::Enums::Instructions easmInstruction, std::vector<Core::Utils::EsetVMArguments>* arguments, int deltaSize);
        void MoveInstructionPtrToMemoryAdress(std::vector<Core::Utils::EsetAssembly>::iterator* instructionPtr, int32_t memoryAddress);
        void Run();
	};
}